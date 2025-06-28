#pragma once
#include <unordered_map>

#include "entity.hpp"


class IComponentArray 
{
public:
    virtual ~IComponentArray() = default;
    virtual void remove(Entity entity) = 0; // This should be the same for every ComponentArray
};


template <typename T>
class ComponentArray : public IComponentArray 
{
    std::unordered_map<Entity, T> components;

public:
    void insert(Entity entity, const T& component);
    void remove(Entity entity) override;
    bool has(Entity entity) const;

    T& get(Entity entity);
    const std::unordered_map<Entity, T>& getAll() const;
};
