#pragma once
#include <memory>
#include <vector>
#include <string>
#include <boost/uuid.hpp>

#include "component.hpp"
#include "../entity.hpp"


namespace uuid = boost::uuids;


class Actor : public IComponent, public ISerializable
{
public:
    ENABLE_REFLECTION_NSERIALIZABLE(Actor)
    
    Actor() = default;
    /// @brief This constructor is used as a temporary placeholder
    /// when deserializing components. 
    Actor(uuid::uuid uuid) : m_uuid(uuid) {};
    Actor(const std::string &name, Entity entity)
        : m_name(name), m_entity(entity), m_uuid(uuid::random_generator()()) {};

    inline Entity GetEntity() const { return this->m_entity; }

    /// @returns a reference to this actor's name
    inline std::string &GetName() { return this->m_name; }
    PROPERTY_GETTER(GetName)

    inline uuid::uuid GetUUID() const { return this->m_uuid; }

    void Serialize(json &j) const override;
    inline void Deserialize(const json &j) override {}
    
private:
    uuid::uuid  m_uuid;
    std::string m_name;
    Entity      m_entity;
};


namespace boost::uuids
{

void to_json(json &j, const boost::uuids::uuid &uuid);
void from_json(const json &j, boost::uuids::uuid &uuid);

}
