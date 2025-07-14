#include "actor.hpp"


void Actor::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(Actor),
        PROP_TO_JSON(m_name),
        PROP_TO_JSON(m_uuid)
    END_SERIALIZATION()
}


void Actor::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_name)
    PROP_FROM_JSON(j, m_uuid)
}


namespace boost::uuids
{

void to_json(json &j, const uuid &u)
{
    j = json{
        {"value", to_string(u)}     
    };
}

void from_json(const json &j, uuid &u)
{
    u = string_generator()(j.at("value").get<std::string>());
}

}
