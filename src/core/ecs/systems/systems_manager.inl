#include "systems_manager.hpp"


template <typename T, typename... Args>
T &SystemsManager::RegisterSystem(Args &&...args)
{
    std::shared_ptr<T> system = std::make_shared<T>(std::forward<Args>(args)...);
    T& ref = *system;
    
    m_systems.push_back(std::move(system));
    
    return ref;
}


template <typename T>
T *SystemsManager::GetSystem()
{
    for (std::shared_ptr<ISystem> &system : this->m_systems)
        if (T *derived = dynamic_cast<T*>(system.get()))
            return derived;
    
    LOG_ERR("System \"{}\" couldn't be found. This may result in unexpected behaviour.", typeid(T).name());
    return nullptr;
}


template <typename T>
void SystemsManager::UpdateSystem(ComponentManager cm, float dt)
{

    for (std::shared_ptr<ISystem> &system : this->m_systems)
    {
        // Check if T is the same type as the pointer
        if (T *derived = dynamic_cast<T*>(system.get()))
        {
            derived->Update(cm, dt);
            return;
        }
    }

    LOG_WARN("System \"{}\" couldn't be updated. Are you sure it's registered?", typeid(T).name());
}
