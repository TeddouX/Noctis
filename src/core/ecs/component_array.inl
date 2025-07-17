#include "component_array.hpp"


template <typename T>
void ComponentArray<T>::Clear()
{
    this->m_components.clear();
}


template <typename T>
void ComponentArray<T>::Insert(Entity entity, std::shared_ptr<T> component)
{
    this->m_components.emplace(entity, component);
}


template <typename T>
void ComponentArray<T>::Remove(Entity entity)
{
    this->m_components.erase(entity);
}


template <typename T>
std::shared_ptr<IComponent> ComponentArray<T>::GetUntyped(Entity entity) const
{
    if (auto search = this->m_components.find(entity); search != this->m_components.end()) 
        return search->second;
    else 
        return nullptr;
}


template <typename T>
bool ComponentArray<T>::Has(Entity entity) const
{
    return this->m_components.find(entity) != m_components.end();
}


template <typename T>
std::shared_ptr<T> ComponentArray<T>::Get(Entity entity)
{
    if (auto search = this->m_components.find(entity); search != this->m_components.end()) 
        return search->second;
    else 
        return nullptr;
}


template <typename T>
const std::unordered_map<Entity, std::shared_ptr<T>> &ComponentArray<T>::GetAll() const
{
    return this->m_components;
}