#include "component_array.hpp"


template <typename T>
void ComponentArray<T>::Clear()
{
    this->m_components.clear();
}


template <typename T>
void ComponentArray<T>::Insert(const Entity &entity, const T &component)
{
    this->m_components.emplace(entity, component);
}


template <typename T>
void ComponentArray<T>::Remove(const Entity &entity)
{
    this->m_components.erase(entity);
}


template <typename T>
std::shared_ptr<IComponent> ComponentArray<T>::GetUntyped(const Entity &entity) const
{
    if (auto search = this->m_components.find(entity); search != this->m_components.end()) 
        return std::make_shared<T>(search->second);
    else 
        return nullptr;
}


template <typename T>
bool ComponentArray<T>::Has(const Entity &entity) const
{
    return this->m_components.find(entity) != m_components.end();
}


template <typename T>
T *ComponentArray<T>::Get(const Entity &entity)
{
    if (auto search = this->m_components.find(entity); search != this->m_components.end()) 
        return &search->second;
    else 
        return nullptr;
}


template <typename T>
std::unordered_map<Entity, T> &ComponentArray<T>::GetAll()
{
    return this->m_components;
}