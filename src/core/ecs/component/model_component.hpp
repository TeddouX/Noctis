#pragma once
#include <memory>

#include "component.hpp"
#include "../../../rendering/model.hpp"


// A ModelComponent stores a pointer to a model that can be rendered
class ModelComponent : public IComponent
{
public:
    ENABLE_REFLECTION(ModelComponent)

    ModelComponent(std::shared_ptr<Model> model)
        : m_model(model) {};

    std::shared_ptr<Model> &GetModel() { return this->m_model; }
    PROPERTY_GETTER(GetModel)

private:
    std::shared_ptr<Model> m_model;
};
