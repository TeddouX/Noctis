#include "actor.hpp"


void Actor::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        PROP_TO_JSON(m_name),
        {"id", this->m_uuid}
    END_SERIALIZATION()
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
