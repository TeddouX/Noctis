#pragma once
#include <memory>
#include <unordered_map>

#include "entity.hpp"


class IComponentArray 
{
public:
    virtual ~IComponentArray() = default;
    virtual void Remove(Entity entity) = 0; // This should be the same for every ComponentArray
};


template <typename T>
class ComponentArray : public IComponentArray 
{
    std::unordered_map<Entity, std::shared_ptr<T>> components;

public:
    void Insert(Entity entity, std::shared_ptr<T> component);

    void Remove(Entity entity) override;

    bool Has(Entity entity) const;

    std::shared_ptr<T> Get(Entity entity);

    const std::unordered_map<Entity, std::shared_ptr<T>> &GetAll() const;
};

#include "component_array.inl"
