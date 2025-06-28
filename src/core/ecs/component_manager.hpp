#pragma once
#include <unordered_map>
#include <typeindex>

#include "entity.hpp"
#include "component_array.hpp"



class ComponentManager 
{
    std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;

public:
    template <typename T> void addComponent(Entity entity, const T& component);
    template <typename T> void removeComponent(Entity entity);
    template <typename T> bool hasComponent(Entity entity) const;
    template <typename T> T& getComponent(Entity entity);

    template <typename T> 
    const std::unordered_map<Entity, T>& getAllComponents() const;

    template <typename T> void registerComponent();

private:
    template <typename T>
    ComponentArray<T>& getComponentArray() const;
};