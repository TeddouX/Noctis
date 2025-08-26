#include "ecs/system/systems_manager.hpp"

namespace Noctis
{

void SystemsManager::UpdateAll(ComponentManager &cm, float dt)
{
    for (std::shared_ptr<ISystem> &system : this->m_systems)
        system->Update(cm, dt);
}

}
