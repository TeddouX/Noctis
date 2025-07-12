#include "scene.hpp"


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
        "Loading scene {} from scene file ({})", 
        this->m_name, this->m_jsonPath.string()
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
        Filesystem::WriteFile(this->m_jsonPath, empty.dump());

        return;
    }

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
        LOG_ERR("Scene file is corrupted, clearing it...")
        Filesystem::WriteFile(this->m_jsonPath, "");

        return;
    }

    if (sceneJson.empty())
        return;

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
}


void Scene::Unload()
{
    LOG_INFO(
        "Unloading scene {} to scene file ({})", 
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

    LOG_INFO("Unloaded scene {}", this->m_name)
}
