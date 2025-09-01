#pragma once
#include <memory>
#include <vector>
#include <typeinfo>

#include "system.hpp"
#include "../component_manager.hpp"
#include "../../logger.hpp"

namespace Noctis
{

// Stores every registered system to help with organisation
class NOCTIS_API SystemsManager
{
    std::vector<std::shared_ptr<ISystem>> m_systems;

public:
    // Register a system of type T
    template<typename T, typename... Args>
    T &RegisterSystem(Args &&...args);
    
    // Returns the system of type T, and if not registered `nullptr`
    template<typename T>
    T *GetSystem();

    // Update all registered systems
    void UpdateAll(ComponentManager &cm, float dt);

    // Update a singular system of type T
    template <typename T>
    void UpdateSystem(ComponentManager &cm, float dt);
};

}

#include "systems_manager.inl"
