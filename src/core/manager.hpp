#pragma once
#include "ecs/systems/render_system.hpp"
#include "ecs/component_manager.hpp"
#include "ecs/all_components.hpp"


#define MANAGER()           Manager::GetInstance()
#define RENDER_SYSTEM()     Manager::GetInstance().GetRenderSystem()
#define COMPONENT_MANAGER() Manager::GetInstance().GetComponentManager()


class Manager
{
public:
    Manager();

    static Manager&   GetInstance();

    inline RenderSystem&     GetRenderSystem()     { return this->m_renderSystem;     };
    inline ComponentManager& GetComponentManager() { return this->m_componentManager; };

private:
    RenderSystem     m_renderSystem;
    ComponentManager m_componentManager;
};
