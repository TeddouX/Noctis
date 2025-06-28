#include "component_manager.hpp"


template <typename T>
void ComponentManager::addComponent(Entity entity, const T& component) 
{
    getComponentArray<T>().insert(entity, component);
}

template <typename T>
void ComponentManager::removeComponent(Entity entity) 
{
    getComponentArray<T>().remove(entity);
}

template <typename T>
bool ComponentManager::hasComponent(Entity entity) const 
{
    const std::unique_ptr<ComponentArray<T>>& array = getComponentArray<T>();
    return array.has(entity);
}

template <typename T>
T& ComponentManager::getComponent(Entity entity) 
{
    return getComponentArray<T>().get(entity);
}

template <typename T>
const std::unordered_map<Entity, T>& ComponentManager::getAllComponents() const 
{
    return getComponentArray<T>().getAll();
}

template <typename T>
void ComponentManager::registerComponent() 
{
    componentArrays[typeid(T)] = std::make_unique<ComponentArray<T>>();
}

template <typename T>
ComponentArray<T>& ComponentManager::getComponentArray() const 
{
    std::type_index type = std::type_index(typeid(T));
    auto it = componentArrays.find(type);
    
    if (it == componentArrays.end()) {
        throw std::runtime_error("Component not registered.");
    }

    return *static_cast<ComponentArray<T>*>(it->second.get());
}
