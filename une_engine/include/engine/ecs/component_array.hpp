#pragma once
#include <memory>
#include <unordered_map>

#include "entity.hpp"
#include "../logger.hpp"


// As this class doesn't do any direct operations on the
// component, forward declaration is possible.
class IComponent;


class IComponentArray 
{
public:
    virtual ~IComponentArray() = default;
    virtual void Clear() = 0;
    virtual void Remove(Entity entity) = 0;
    virtual bool Has(Entity entity) const = 0;
    virtual std::shared_ptr<IComponent> GetUntyped(Entity entity) const = 0;
};


template <typename T>
class ComponentArray : public IComponentArray 
{
    std::unordered_map<Entity, std::shared_ptr<T>> m_components;

public:
    void Clear() override;

    void Insert(Entity entity, std::shared_ptr<T> component);

    void Remove(Entity entity) override;

    std::shared_ptr<IComponent> GetUntyped(Entity entity) const override;

    bool Has(Entity entity) const override;

    std::shared_ptr<T> Get(Entity entity);

    const std::unordered_map<Entity, std::shared_ptr<T>> &GetAll() const;
};

#include "component_array.inl"
