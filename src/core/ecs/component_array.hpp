#pragma once
#include <memory>
#include <unordered_map>

#include "entity.hpp"
#include "component/component.hpp"
#include "../logger.hpp"


class IComponentArray 
{
public:
    virtual ~IComponentArray() = default;
    virtual void Remove(Entity entity) = 0;
    virtual std::shared_ptr<IComponent> GetUntyped(Entity entity) const = 0;
    virtual bool Has(Entity entity) const = 0;
};


template <typename T>
class ComponentArray : public IComponentArray 
{
    std::unordered_map<Entity, std::shared_ptr<T>> m_components;

public:
    void Insert(Entity entity, std::shared_ptr<T> component);

    void Remove(Entity entity) override;

    std::shared_ptr<IComponent> GetUntyped(Entity entity) const override;

    bool Has(Entity entity) const override;

    std::shared_ptr<T> Get(Entity entity);

    const std::unordered_map<Entity, std::shared_ptr<T>> &GetAll() const;
};

#include "component_array.inl"
