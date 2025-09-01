#pragma once
#include <memory>

#include "component.hpp"
#include "../../property/asset_property.hpp"
#include "../../asset/asset_manager.hpp"
#include "../../rendering/model.hpp"

namespace Noctis
{

// A ModelComponent stores a pointer to a model that can be rendered
class NOCTIS_API ModelComponent : public IComponent
{
public:
    REGISTER_COMPONENT(ModelComponent, "Model")

    ModelComponent() = default;
    ModelComponent(std::shared_ptr<IAsset<Model>> model)
        : m_model(model) {};

    std::shared_ptr<Model> GetModel() { return this->m_model->Asset; }

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

    std::vector<std::shared_ptr<IPropertyBase>> GetProperties() override;

private:
    std::shared_ptr<IAsset<Model>> m_model;
};

}
