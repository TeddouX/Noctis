#include "manager.hpp"


Manager::Manager()
{
    // Register all components
    this->m_componentManager.RegisterComponent<ModelComponent>();
    this->m_componentManager.RegisterComponent<TransformComponent>();
}


Manager& Manager::GetInstance()
{
    static Manager manager;
    return manager;
}
