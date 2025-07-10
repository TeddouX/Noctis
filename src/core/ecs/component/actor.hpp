#pragma once
#include <memory>
#include <vector>
#include <string>
#include <boost/uuid.hpp>

#include "component.hpp"
#include "../entity.hpp"


class Actor : public IComponent
{
public:
    ENABLE_REFLECTION(Actor)
    
    Actor() = default;
    // This constructor is used as a temporary placeholder
    // when deserializing components. 
    Actor(boost::uuids::uuid uuid) : m_uuid(uuid) {};
    Actor(const std::string &name, Entity entity)
        : m_name(name), m_entity(entity), m_uuid(boost::uuids::random_generator()()) {};

    inline Entity GetEntity() const { return this->m_entity; }

    // Returns a reference to this actor's name
    inline std::string &GetName() { return this->m_name; }
    PROPERTY_GETTER(GetName)

    inline boost::uuids::uuid GetUUID() const { return this->m_uuid; }
    
private:
    boost::uuids::uuid m_uuid;
    std::string        m_name;
    Entity             m_entity;
};