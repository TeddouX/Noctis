#pragma once
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
    std::unordered_map<Entity, T> components;

public:
    void Insert(Entity entity, const T& component);

    void Remove(Entity entity) override;

    bool Has(Entity entity) const;

    T& Get(Entity entity);

    const std::unordered_map<Entity, T>& GetAll() const;
};

#include "component_array.inl"
