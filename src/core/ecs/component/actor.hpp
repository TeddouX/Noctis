#pragma once
#include <memory>
#include <vector>
#include <string>

#include "component.hpp"
#include "../entity.hpp"


class Actor : public IComponent
{
public:
    ENABLE_REFLECTION(Actor)
    
    Actor(const std::string &name, const Entity *entity);

    inline const Entity *GetEntity() const { return this->m_entity; }

    // Returns a reference to this actor's name
    inline std::string &GetName() { return this->m_name; }
    PROPERTY_GETTER(GetName)
    
private:
    std::string m_name;
    const Entity *m_entity;
};