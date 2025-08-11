#pragma once
#include <memory>

#include "component.hpp"
#include "property/model_property.hpp"
#include "../../asset_manager.hpp"
#include "../../rendering/model.hpp"


// A ModelComponent stores a pointer to a model that can be rendered
class NOCTIS_API ModelComponent : public IComponent
{
public:
    REGISTER_COMPONENT(ModelComponent, "Model")

    ModelComponent() = default;
    ModelComponent(std::shared_ptr<Model> model)
        : m_model(model) {};

    std::shared_ptr<Model> &GetModel() { return this->m_model; }

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

    std::vector<std::shared_ptr<IPropertyBase>> GetProperties() override;

private:
    std::shared_ptr<Model> m_model;
};
