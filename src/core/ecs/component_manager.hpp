#pragma once
#include <unordered_map>
#include <typeindex>
#include <stdexcept>

#include "entity.hpp"
#include "component_array.hpp"


class ComponentManager 
{
    std::unordered_map<std::type_index, std::unique_ptr<IComponentArray>> componentArrays;

public:
    template <typename T> 
    void AddComponent(Entity entity, const T& component)
    {
        this->GetComponentArray<T>().Insert(entity, component);
    }

    template <typename T> 
    void RemoveComponent(Entity entity)
    {
        this->GetComponentArray<T>().Remove(entity);
    }

    template <typename T> 
    bool HasComponent(Entity entity) const
    {
        const ComponentArray<T>& array = this->GetComponentArray<T>();
        return array.Has(entity);
    }

    template <typename T> T&   
    GetComponent(Entity entity) const
    {
        return this->GetComponentArray<T>().Get(entity);
    }

    template <typename T> 
    const std::unordered_map<Entity, T>& GetAllComponents() const
    {
        return this->GetComponentArray<T>().GetAll();
    }

    template <typename T> 
    void RegisterComponent()
    {
        componentArrays.emplace(typeid(T), std::make_unique<ComponentArray<T>>());
    }

private:
    template <typename T>
    ComponentArray<T>& GetComponentArray() const
    {
        std::type_index type = std::type_index(typeid(T));
        auto it = this->componentArrays.find(type);
        
        if (it == this->componentArrays.end()) {
            throw std::runtime_error("Component not registered.");
        }

        return *static_cast<ComponentArray<T>*>(it->second.get());
    }
};