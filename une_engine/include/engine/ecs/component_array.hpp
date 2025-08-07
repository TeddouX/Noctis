#pragma once
#include <memory>
#include <unordered_map>

#include "../logger.hpp"


// As this class doesn't do any direct operations on the
// component, forward declaration is possible.
class IComponent;
class Entity;


class IComponentArray 
{
public:
    virtual ~IComponentArray() = default;
    virtual void Clear() = 0;
    virtual void Remove(const Entity &entity) = 0;
    virtual bool Has(const Entity &entity) const = 0;
    virtual std::shared_ptr<IComponent> GetUntyped(const Entity &entity) const = 0;
};


template <typename T>
class ComponentArray : public IComponentArray 
{
    std::unordered_map<Entity, T> m_components;

public:
    void Clear() override;

    void Insert(const Entity &entity, const T &component);

    void Remove(const Entity &entity) override;

    std::shared_ptr<IComponent> GetUntyped(const Entity &entity) const override;

    bool Has(const Entity &entity) const override;

    T *Get(const Entity &entity);

    std::unordered_map<Entity, T> &GetAll();
};

#include "component_array.inl"
