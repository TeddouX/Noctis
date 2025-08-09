#include "scene.hpp"


template <typename T>
void Scene::UpdateSystem(float dt)
{
    this->m_systemsManager.UpdateSystem<T>(
        this->m_componentManager, 
        dt
    );
}

template <typename T>
T *Scene::GetSystem()
{
    return this->m_systemsManager.GetSystem<T>();
}
