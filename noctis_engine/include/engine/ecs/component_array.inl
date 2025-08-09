#include "component_array.hpp"


template <typename T>
void ComponentArray<T>::Clear()
{
    this->m_components.clear();
}


template <typename T>
void ComponentArray<T>::Insert(const Entity &entity, std::shared_ptr<T> component)
{
    this->m_components.emplace(entity, component);
}


template <typename T>
void ComponentArray<T>::Remove(const Entity &entity)
{
    this->m_components.erase(entity);
}


template <typename T>
std::shared_ptr<IComponent> ComponentArray<T>::GetUntyped(const Entity &entity)
{
    if (this->m_components.contains(entity))
        return this->m_components.at(entity);
    else 
        return nullptr;
}


template <typename T>
bool ComponentArray<T>::Has(const Entity &entity) const
{
    return this->m_components.find(entity) != m_components.end();
}


template <typename T>
std::shared_ptr<T> ComponentArray<T>::Get(const Entity &entity)
{
    if (this->m_components.contains(entity)) 
        return this->m_components.at(entity);
    else 
        return nullptr;
}


template <typename T>
std::unordered_map<Entity, std::shared_ptr<T>> &ComponentArray<T>::GetAll()
{
    return this->m_components;
}