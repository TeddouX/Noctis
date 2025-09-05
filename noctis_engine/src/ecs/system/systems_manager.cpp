#include "ecs/system/systems_manager.hpp"

namespace Noctis
{

void SystemsManager::UpdateAll(float dt)
{
    for (std::shared_ptr<ISystem> &system : this->m_systems)
        system->Update(*m_cm, dt);
}

}
