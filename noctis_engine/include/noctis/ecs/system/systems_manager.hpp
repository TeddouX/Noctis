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
public:
    SystemsManager(std::shared_ptr<ComponentManager> cm)
        : m_cm(cm) {}

    // Register a system of type T
    template<typename T, typename... Args>
    T &RegisterSystem(Args &&...args);
    
    // Returns the system of type T, and if not registered `nullptr`
    template<typename T>
    T *GetSystem();

    // Update all registered systems
    void UpdateAll(float dt);

    // Update a singular system of type T
    template <typename T>
    void UpdateSystem(float dt);

private:
    std::vector<std::shared_ptr<ISystem>> m_systems;
    std::shared_ptr<ComponentManager> m_cm;
};

}

#include "systems_manager.inl"
