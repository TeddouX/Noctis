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
    return this->GetComponentArray<T>().Has(entity);
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
    std::type_index type(typeid(T));
    
    auto it = this->m_componentArrays.find(type);
    if (it == this->m_componentArrays.end()) 
    {
        ComponentManager *nonConstThis = const_cast<ComponentManager *>(this);
        nonConstThis->RegisterComponent<T>();
        it = m_componentArrays.find(type);
    }

    return *std::static_pointer_cast<ComponentArray<T>>(it->second);
}
