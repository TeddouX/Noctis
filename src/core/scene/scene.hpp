#pragma once
#include <memory>
#include <filesystem>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <fmt/format.h>

#include "../project.hpp"
#include "../logger.hpp"
#include "../ecs/entity.hpp"
#include "../ecs/component_manager.hpp"
#include "../ecs/components/all_components.hpp"
#include "../ecs/systems/systems_manager.hpp"
#include "../ecs/systems/render_system.hpp"


namespace fs = std::filesystem;
using json = nlohmann::json;


class Scene
{
public:
    Scene(const std::string &name);

    inline void  AddEntity(Entity &entity) { this->m_sceneEntities.push_back(entity); }
    void         RemoveEntity(Entity entity);

    inline const std::vector<Entity> GetAllEntities() const { return this->m_sceneEntities; }

    inline std::string GetName() const { return this->m_name; };

    inline ComponentManager &GetComponentManager() { return this->m_componentManager; }
    
    void UpdateAllSystems(float dt);
    
    template <typename T>
    void UpdateSystem(float dt);

    template <typename T>
    T   *GetSystem();

    void Load();
    void Unload();

private:
    std::vector<Entity> m_sceneEntities;
    ComponentManager    m_componentManager;
    SystemsManager      m_systemsManager;
    
    std::string         m_name;
};

#include "scene.inl"
