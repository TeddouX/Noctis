#pragma once
#include <memory>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>

#include "engine.hpp"
#include "ecs/entity.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/system/systems_manager.hpp"

namespace Noctis
{

class NOCTIS_API Scene 
{
public:
    Scene(const std::string &name)
        : m_name(name),
        m_cm(std::make_shared<ComponentManager>()),
        m_sm(m_cm) {}

    void AddEntity(const Entity &entity) { m_entities.push_back(entity); }
    void RemoveEntity(const Entity &entity);

    const std::vector<Entity> &GetAllEntities() { return m_entities; }

    std::shared_ptr<ComponentManager> GetComponentManager() { return m_cm; }
    SystemsManager   &GetSystemsManager() { return m_sm; }

    const std::string &GetName() const { return m_name; }

    nlohmann::json Serialize();

    void Load(const nlohmann::json &j);
    void Unload();

private:
    std::vector<Entity> m_entities;
    std::string m_name;
    
    std::shared_ptr<ComponentManager> m_cm;
    SystemsManager   m_sm;
};

} // namespace Noctis
