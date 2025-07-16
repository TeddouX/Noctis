#pragma once
#include <memory>

#include "component.hpp"
#include "../../../rendering/model.hpp"
#include "../../asset_manager.hpp"


// A ModelComponent stores a pointer to a model that can be rendered
class ModelComponent : public IComponent, public ISerializable
{
public:
    ENABLE_REFLECTION(ModelComponent)

    ModelComponent() = default;
    ModelComponent(std::shared_ptr<Model> model)
        : m_model(model) {};

    std::shared_ptr<Model> &GetModel() { return this->m_model; }
    PROPERTY_GETTER(GetModel)

    void Serialize(json &j) const override;
    void Deserialize(const json &j) override;

private:
    std::shared_ptr<Model> m_model;
};
