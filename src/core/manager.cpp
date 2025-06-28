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


RenderSystem& Manager::GetRenderSystem()
{
    return this->m_renderSystem;
}

ComponentManager& Manager::GetComponentManager()
{
    return this->m_componentManager;
}
