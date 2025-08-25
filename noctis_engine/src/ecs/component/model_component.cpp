#include "ecs/component/model_component.hpp"


void ModelComponent::Serialize(json &j) const
{
    START_SERIALIZATION(j)
        {"model", this->m_model->Name}
    END_SERIALIZATION()
}


void ModelComponent::Deserialize(const json &j)
{
    this->m_model = ASSET_MANAGER()->GetTyped<Model>(AssetType::MODEL, j["model"]);
}


std::vector<std::shared_ptr<IPropertyBase>> ModelComponent::GetProperties()
{
    return { 
        std::make_shared<AssetProperty>(
            GETTER_FOR(std::dynamic_pointer_cast<IAssetBase>(this->m_model)), "Model"
        ) 
    };
}
