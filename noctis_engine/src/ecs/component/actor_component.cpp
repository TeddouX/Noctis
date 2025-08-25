#include "ecs/component/actor_component.hpp"


void Actor::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        PROP_TO_JSON(m_name),
        PROP_TO_JSON(m_uuid)
    END_SERIALIZATION()
}


void Actor::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_name)
    PROP_FROM_JSON(j, m_uuid)
}
