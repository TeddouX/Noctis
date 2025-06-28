#include "component_array.hpp"


template <typename T>
void ComponentArray<T>::insert(Entity entity, const T& component) 
{
    this->components[entity] = component;
}

template <typename T>
void ComponentArray<T>::remove(Entity entity) 
{
    this->components.erase(entity);
}

template <typename T>
bool ComponentArray<T>::has(Entity entity) const 
{
    return this->components.find(entity) != components.end();
}

template <typename T>
T& ComponentArray<T>::get(Entity entity) 
{
    return this->components.at(entity);
}

template <typename T>
const std::unordered_map<Entity, T>& ComponentArray<T>::getAll() const 
{
    return this->components;
}
