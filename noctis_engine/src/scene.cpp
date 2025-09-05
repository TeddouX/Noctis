#include "scene.hpp"

#include <fstream>
#include <fmt/format.h>

#include "logger.hpp"
#include "ecs/component/actor_component.hpp"
#include "ecs/system/render_system.hpp"
#include "ecs/system/lighting_system.hpp"

namespace Noctis
{

void Scene::RemoveEntity(const Entity &entity)
{
    m_entities.erase(
        std::remove(
            m_entities.begin(), 
            m_entities.end(), 
            entity
        ), 
        m_entities.end()
    );
}

nlohmann::json Scene::Serialize()
{
    json sceneJson;
    sceneJson["name"] = this->m_name;

    json allActorsJson = json::array();
    for (Entity entity : this->m_entities)
    {
        const auto components = m_cm->GetAllComponents(entity);
        auto actor = m_cm->GetComponent<Actor>(entity);

        json actorSerializedJson;
        actor->Serialize(actorSerializedJson);

        json actorJson;
        actorJson["actor"] = actorSerializedJson;

        json componentsJson = json::array();
        for (std::shared_ptr<IComponent> component : components)
        {
            // Actor is already serialized
            if (std::dynamic_pointer_cast<Actor>(component))
                continue;

            componentsJson.push_back(component);
        }

        actorJson["components"] = componentsJson;
        allActorsJson.push_back(actorJson);
    }

    sceneJson["actors"] = allActorsJson;

    return sceneJson;
}

void Scene::Load(const nlohmann::json &j)
{
    if (j.empty())
        return;

    std::unordered_map<UUIDv4, std::shared_ptr<Transform>> transformsMap;
    // Get all the scene's actors from json
    json allActorsJson = j["actors"];
    for (const json &actorJson : allActorsJson)
    {
        std::shared_ptr<IComponent> actorUntyped = actorJson["actor"];
        auto actor = std::dynamic_pointer_cast<Actor>(actorUntyped);

        // This means the actor was not deserialized correctly
        if (!actor)
        {
            LOG_ERR("Invalid actor json: {}", actorJson["actor"].dump());
            continue;
        }

        Entity entity(m_cm.get());
        actor->SetEntity(entity);

        // Add the entity to this scene's entity list
        AddEntity(entity);

        // Add the actor component to the entity
        entity.AddComponent<Actor>(actor);

        json allComponentsJson = actorJson["components"];
        for (const json &componentJson : allComponentsJson)
        {
            std::shared_ptr<IComponent> serializableComponent = componentJson;

            // If the component is a transform, add it to the map for 
            // later referencing
            if (auto transform = std::dynamic_pointer_cast<Transform>(serializableComponent))
                transformsMap.emplace(actor->GetUUID(), transform);

            ComponentRegistry::GetInstance().AddComponentFromName(
                // The component's name
                componentJson["type"],
                // The entity it will be added to
                entity,
                // Pointer to the actual component
                std::dynamic_pointer_cast<IComponent>(serializableComponent)
            );
        }
    }

    // Correctly parent all the transforms
    // using the transform map built during
    // deserialization
    auto allTransforms = m_cm->GetEntitiesWith<Transform>();
    for (auto &[entity, transform] : allTransforms)
    {
        // Is the transform parented to any 
        // other transform ?
        if (!transform->IsChild())
            continue;

        auto parent = transform->GetParent();

        // Was its parent built during deserialization ?
        if (!parent->IsTemporary())
            continue;

        // Because the parent needs to be set
        // to an existing transform ptr in the scene
        auto correctParent = transformsMap.at(parent->GetActor()->GetUUID());
        transform->SetParent(correctParent.get());
    }
}

void Scene::Unload()
{
    Entity::ResetCount();
    
    m_cm->Clear();
    m_entities.clear();
}

}
