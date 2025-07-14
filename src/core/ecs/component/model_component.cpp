#include "model_component.hpp"


void ModelComponent::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(ModelComponent),
        PROP_TO_JSON(m_model)
    END_SERIALIZATION()
}


void ModelComponent::Deserialize(const json &j)
{
    PROP_FROM_JSON(j, m_model)
}
