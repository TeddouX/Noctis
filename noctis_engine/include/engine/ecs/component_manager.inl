#include "component_manager.hpp"

namespace Noctis
{

template <typename T> 
void ComponentManager::AddComponent(const Entity &entity, std::shared_ptr<T> component)
{
    this->GetComponentArray<T>().Insert(entity, component);
}


template <typename T> 
void ComponentManager::RemoveComponent(const Entity &entity)
{
    this->GetComponentArray<T>().Remove(entity);
}


template <typename T> 
bool ComponentManager::HasComponent(const Entity &entity)
{
    return this->GetComponentArray<T>().Has(entity);
}


template <typename T> 
std::shared_ptr<T> ComponentManager::GetComponent(const Entity &entity)
{
    return this->GetComponentArray<T>().Get(entity);
}


template <typename T> 
std::unordered_map<Entity, std::shared_ptr<T>> &ComponentManager::GetEntitiesWith()
{
    return this->GetComponentArray<T>().GetAll();
}


template <typename T> 
void ComponentManager::RegisterComponent()
{
    if constexpr (!std::is_base_of_v<IComponent, T> || !std::is_default_constructible_v<T>)
        return;

    this->m_componentArrays.emplace(typeid(T), std::make_shared<ComponentArray<T>>());
}


template <typename T>
ComponentArray<T> &ComponentManager::GetComponentArray()
{
    std::type_index type(typeid(T));
    
    std::shared_ptr<IComponentArray> arrPtr;
    if (!this->m_componentArrays.contains(type))
        this->RegisterComponent<T>();
    
    arrPtr = this->m_componentArrays.at(type);

    return *std::static_pointer_cast<ComponentArray<T>>(arrPtr);
}

}
