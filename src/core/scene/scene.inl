#include "scene.hpp"


template <typename T>
void Scene::UpdateSystem(float dt)
{
    this->m_systemsManager.UpdateSystem<T>(
        this->m_componentManager, 
        dt
    );
}
