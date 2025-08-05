#include "scene/scene.hpp"


Scene::Scene(const fs::path &path)
    : m_jsonPath(path)
{
    if (!fs::is_regular_file(path))
    {
        LOG_ERR("Path {} is not a regular file.", path.string())
        return;
    }
    
    if (path.extension() != ".scene")
    {
        LOG_ERR("File {} is not a scene file.", path.string())
        return;
    }

    // File name without extensions
    this->m_name = path.stem().string();
    this->RegisterSystems();
}

Scene::Scene(const std::string &name, const fs::path &scenesRoot)
    : m_name(name)
{
    this->m_jsonPath = fmt::format("{}\\{}.scene", scenesRoot.string(), name);
    this->RegisterSystems();
}

void Scene::RegisterSystems()
{
    // Register all systems
    this->m_systemsManager.RegisterSystem<RenderSystem>();
    this->m_systemsManager.RegisterSystem<LightingSystem>();
}


void Scene::RemoveEntity(Entity entity)
{
    this->m_entities.erase(
        std::remove(
            this->m_entities.begin(), 
            this->m_entities.end(), 
            entity
        ), 
        this->m_entities.end()
    );
}


void Scene::UpdateAllSystems(float dt)
{
    this->m_systemsManager.UpdateAll(this->m_componentManager, dt); 
}

void Scene::Load()
{
    LOG_INFO(
        "Loading scene {} from scene file {}", 
        this->m_name, 
        this->m_jsonPath.string()
    )

    if (!fs::exists(this->m_jsonPath))
    {
        LOG_WARN(
            "Scene file ({}) for scene {} doesn't exist. Creating one now...", 
            this->m_jsonPath.string(), 
            this->m_name
        )

        // Fill the file with an empty json object
        json empty = json::object();

#if COMPRESS_SCENE_DATA
        Filesystem::WriteCBOR(this->m_jsonPath, json::to_cbor(empty));
#else
        Filesystem::WriteFile(this->m_jsonPath, empty.dump());
#endif

        return;
    }

    // Read data from this scene's file
#if COMPRESS_SCENE_DATA
    std::vector<uint8_t> cborData = Filesystem::ReadCBOR(this->m_jsonPath);
#else
    std::string jsonFileContents = Filesystem::GetFileContents(this->m_jsonPath); 
#endif

    json sceneJson;

    try
    {
#if COMPRESS_SCENE_DATA
        sceneJson = json::from_cbor(cborData);
#else
        sceneJson = json::parse(jsonFileContents);
#endif
    }
    catch (const json::parse_error&)
    {
        LOG_ERR("Scene file is corrupted so it couldn't be loaded...")
        // Filesystem::WriteFile(this->m_jsonPath, "");

        return;
    }

    if (sceneJson.empty())
        return;

    // Eventual serialization errors
    std::string nameInJson = sceneJson["name"].get<std::string>();
    if (nameInJson != this->m_name)
    {
        LOG_ERR(
            "Name mismatch in scene file {} (expected {}, got {})",
            this->m_jsonPath.string(),
            this->m_name,
            nameInJson
        )

        return;
    }

    std::unordered_map<UUIDv4, std::shared_ptr<Transform>> transformsMap;
    // Get all the scene's actors from json
    json allActorsJson = sceneJson["actors"];
    for (const json &actorJson : allActorsJson)
    {
        std::shared_ptr<ISerializable> actorUntyped = actorJson["actor"];
        auto actor = std::dynamic_pointer_cast<Actor>(actorUntyped);

        // This means the actor was not deserialized correctly
        if (!actor)
        {
            LOG_ERR("Invalid actor json: {}", actorJson["actor"].dump())
            continue;
        }

        
        Entity entity = Entity::Create();
        actor->SetEntity(entity);

        // Add the entity to this scene's entity list
        this->AddEntity(entity);

        // Add the actor component to the entity
        this->m_componentManager.AddComponent<Actor>(entity, *actor);

        json allComponentsJson = actorJson["components"];
        for (const json &componentJson : allComponentsJson)
        {
            std::shared_ptr<ISerializable> serializableComponent = componentJson;

            // If the component is a transform, add it to the map for 
            // later referencing
            if (auto transform = std::dynamic_pointer_cast<Transform>(serializableComponent))
                transformsMap.emplace(actor->GetUUID(), transform);


            ComponentRegistry::GetInstance().AddComponentFromName(
                // The component's name
                componentJson["type"],
                // The entity it will be added to
                entity,
                // This scene's component manager 
                this->m_componentManager,
                // Pointer to the actual component
                std::dynamic_pointer_cast<IComponent>(serializableComponent)
            );
        }
    }

    // Correctly parent all the transforms
    // using the transform map built during
    // deserialization
    auto allTransforms = this->m_componentManager.GetEntitiesWith<Transform>();
    for (auto &[entity, transform] : allTransforms)
    {
        // Is the transform parented to any 
        // other transform ?
        if (!transform.IsChild())
            continue;

        auto parent = transform.GetParent();

        // Was its parent built during deserialization ?
        if (!parent->IsTemporary())
            continue;

        // Because the parent needs to be set
        // to an existing transform ptr in the scene
        auto correctParent = transformsMap.at(parent->GetActor()->GetUUID());
        transform.SetParent(correctParent.get());
    }

    LOG_INFO("Loaded scene {}", this->m_name)
}


void Scene::Unload()
{
    this->Save();

    Entity::ResetCount();
    this->m_componentManager.Clear();
    this->m_entities.clear();
}


void Scene::Save()
{
    LOG_INFO(
        "Saving scene {} to scene file ({})", 
        this->m_name, this->m_jsonPath.string()
    )

    json sceneJson;
    sceneJson["name"] = this->m_name;

    json allActorsJson = json::array();
    for (Entity entity : this->m_entities)
    {
        const auto components = this->m_componentManager.GetAllComponents(entity);
        auto actor = this->m_componentManager.GetComponent<Actor>(entity);

        json actorSerializedJson;
        actor->Serialize(actorSerializedJson);

        json actorJson;
        actorJson["actor"] = actorSerializedJson;

        json componentsJson = json::array();
        // Serialize all components that inherit from ISerializable.
        for (std::shared_ptr<IComponent> component : components)
        {
            // Actor is already serialized
            if (std::dynamic_pointer_cast<Actor>(component))
                continue;

            // Is the component serializable ?
            if (auto serializable = std::dynamic_pointer_cast<ISerializable>(component))
                componentsJson.push_back(serializable);
        }
            
        actorJson["components"] = componentsJson;
        allActorsJson.push_back(actorJson);
    }

    sceneJson["actors"] = allActorsJson;

    // 536 bytes -> 413 bytes for a scene with only one cube
    // May be subject to change
#if COMPRESS_SCENE_DATA
    std::vector<uint8_t> compressed = json::to_cbor(sceneJson);
    Filesystem::WriteCBOR(this->m_jsonPath, compressed);
#else
    Filesystem::WriteFile(this->m_jsonPath, sceneJson.dump());
#endif

    LOG_INFO("Saved scene {}", this->m_name)
}
