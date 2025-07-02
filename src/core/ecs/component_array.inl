#include "component_array.hpp"


template <typename T>
void ComponentArray<T>::Insert(Entity entity, const T& component)
{
    this->components[entity] = component;
}


template <typename T>
void ComponentArray<T>::Remove(Entity entity)
{
    this->components.erase(entity);
}


template <typename T>
bool ComponentArray<T>::Has(Entity entity) const
{
    return this->components.find(entity) != components.end();
}


template <typename T>
T& ComponentArray<T>::Get(Entity entity)
{
    return this->components.at(entity);
}


template <typename T>
const std::unordered_map<Entity, T>& ComponentArray<T>::GetAll() const
{
    return this->components;
}