#include "component_manager.hpp"


template <typename T> 
void ComponentManager::AddComponent(Entity entity, std::shared_ptr<T> component)
{
    this->GetComponentArray<T>().Insert(entity, component);
}


template <typename T> 
void ComponentManager::RemoveComponent(Entity entity)
{
    this->GetComponentArray<T>().Remove(entity);
}


template <typename T> 
bool ComponentManager::HasComponent(Entity entity) const
{
    const ComponentArray<T>& array = this->GetComponentArray<T>();
    return array.Has(entity);
}


template <typename T> 
std::shared_ptr<T> ComponentManager::GetComponent(Entity entity) const
{
    return this->GetComponentArray<T>().Get(entity);
}


template <typename T> 
const std::unordered_map<Entity, std::shared_ptr<T>> &ComponentManager::GetEntities() const
{
    return this->GetComponentArray<T>().GetAll();
}


template <typename T> 
void ComponentManager::RegisterComponent()
{
    this->m_componentArrays.emplace(typeid(T), std::make_shared<ComponentArray<T>>());
}


template <typename T>
ComponentArray<T> &ComponentManager::GetComponentArray() const
{
    std::type_index type = std::type_index(typeid(T));
    auto it = this->m_componentArrays.find(type);
    
    if (it == this->m_componentArrays.end()) {
        LOG_ERR("Component \"{}\" not registered.", typeid(T).name())
        exit(1);
    }

    return *static_cast<ComponentArray<T>*>(it->second.get());
}