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
    void Insert(Entity entity, const T& component)
    {
        this->components[entity] = component;
    }

    void Remove(Entity entity) override
    {
        this->components.erase(entity);
    }

    bool Has(Entity entity) const
    {
        return this->components.find(entity) != components.end();
    }

    T& Get(Entity entity)
    {
        return this->components.at(entity);
    }

    const std::unordered_map<Entity, T>& GetAll() const
    {
        return this->components;
    }
};
