#pragma once
#include <memory>
#include <string>

#include "component.hpp"
#include "../entity.hpp"
#include "../../utils/uuid.hpp"


class NOCTIS_API Actor : public IComponent
{
public:
    REGISTER_COMPONENT(Actor, "Actor")

    Actor() = default;
    /// @brief This constructor is used as a temporary placeholder
    /// when deserializing components. 
    Actor(UUIDv4 uuid) : m_uuid(uuid) {};
    Actor(const std::string &name, Entity entity)
        : m_name(name), m_entity(entity), m_uuid(UUIDv4::Generate()) {};

    inline void SetEntity(Entity e) { this->m_entity = e; }
    inline Entity GetEntity() const { return this->m_entity; }

    /// @returns a reference to this actor's name
    inline std::string &GetName() { return this->m_name; }

    inline UUIDv4 GetUUID() const { return this->m_uuid; }

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

private:
    std::string m_name;
    Entity m_entity;
    UUIDv4 m_uuid;
};

