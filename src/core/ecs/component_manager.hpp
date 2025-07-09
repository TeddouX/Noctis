#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

#include "entity.hpp"
#include "component_array.hpp"
#include "../logger.hpp"


class ComponentManager 
{
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> m_componentArrays;

public:
    template <typename T> 
    void AddComponent(Entity entity, std::shared_ptr<T> component);

    template <typename T> 
    void RemoveComponent(Entity entity);
    
    template <typename T> 
    bool HasComponent(Entity entity) const;

    template <typename T> 
    std::shared_ptr<T> GetComponent(Entity entity) const;

    template <typename T> 
    const std::unordered_map<Entity, std::shared_ptr<T>> &GetEntities() const;

    const std::vector<std::shared_ptr<IComponent>> GetAllComponents(Entity entity) const;

private:
    template <typename T> 
    void RegisterComponent();

    template <typename T>
    ComponentArray<T> &GetComponentArray() const;
};

#include "component_manager.inl"
