#pragma once
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fmt/format.h>

#include "../logger.hpp"
#include "../ecs/entity.hpp"
#include "../ecs/component_manager.hpp"
#include "../ecs/component/all_components.hpp"
#include "../ecs/system/systems_manager.hpp"
#include "../ecs/system/render_system.hpp"
#include "../ecs/system/lighting_system.hpp"


#define COMPRESS_SCENE_DATA 1


namespace fs = std::filesystem;
using json = nlohmann::json;

namespace Noctis
{

class NOCTIS_API Scene
{
public:
    Scene(const fs::path &path);
    Scene(const std::string &name, const fs::path &scenesRoot);

    /// @brief Adds an entity to this scene's entity list
    void AddEntity(Entity entity) { this->m_entities.push_back(entity); }

    /// @brief Removes an entity from this scene's, its children 
    /// and its associated components (unfinished)
    void RemoveEntity(Entity entity);

    /// @returns All this scene's entities 
    const std::vector<Entity> &GetAllEntities() const { return this->m_entities; }

    /// @returns The currently selected entity (editor only) 
    Entity &GetSelectedEntity() { return this->m_selectedEntity; }
 
    /// @brief Sets the currently selected entity (editor only) 
    void SetSelectedEntity(Entity entity) { this->m_selectedEntity = entity; }

    /// @returns This scene's name
    std::string GetName() const { return this->m_name; };

    /// @returns This scene's component manager
    ComponentManager &GetComponentManager() { return this->m_componentManager; }

    /// @brief Updates all systems registered on this scene
    void UpdateAllSystems(float dt);
    
    /// @brief Update system of type T
    template <typename T>
    void UpdateSystem(float dt);

    /// @returns The systems of type T, or `nullptr` if 
    /// the system isn't registered on this scene
    template <typename T>
    T *GetSystem();

    /// @brief Loads all this scene's data from its associated JSON file
    void Load();

    /// @brief Unload this scene and saves all its data to its json file
    void Unload();

    /// @brief Save this scene and saves all its data to its json file
    void Save();

private:
    std::vector<Entity>  m_entities;
    Entity               m_selectedEntity;
    ComponentManager     m_componentManager;
    SystemsManager       m_systemsManager;
    
    std::string          m_name;
    fs::path             m_jsonPath;

    void RegisterSystems();
};

}

#include "scene.inl"
