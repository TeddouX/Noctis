#include "model_component.hpp"


void ModelComponent::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        COMPONENT_TO_JSON(ModelComponent),
        {"model", this->m_model->GetName()}
    END_SERIALIZATION()
}


void ModelComponent::Deserialize(const json &j)
{
    // PROP_FROM_JSON(j, m_model)
    // Get a shared ptr to the model from the model name
    this->m_model = AssetManager::GetInstance().GetModel(j["model"]);
}
