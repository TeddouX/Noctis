#pragma once
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

#include "component_array.hpp"
#include "../logger.hpp"

namespace Noctis
{

class Entity;


class NOCTIS_API ComponentManager 
{
    std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> m_componentArrays;

public:
    template <typename T> 
    void AddComponent(const Entity &entity, std::shared_ptr<T> component);

    template <typename T> 
    void RemoveComponent(const Entity &entity);
    
    template <typename T> 
    bool HasComponent(const Entity &entity);

    template <typename T> 
    std::shared_ptr<T> GetComponent(const Entity &entity);

    template <typename T> 
    std::unordered_map<Entity, std::shared_ptr<T>> &GetEntitiesWith();

    std::vector<std::shared_ptr<IComponent>> GetAllComponents(const Entity &entity);

    void Clear();

private:
    template <typename T> 
    void RegisterComponent();

    template <typename T>
    ComponentArray<T> &GetComponentArray();
};

}

#include "component_manager.inl"
