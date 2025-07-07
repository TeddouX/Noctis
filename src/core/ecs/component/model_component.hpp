#pragma once
#include <memory>

#include "component.hpp"
#include "../../../rendering/model.hpp"


// A ModelComponent stores a pointer to a model that can be rendered
class ModelComponent : public IComponent
{
public:
    ENABLE_REFLECTION(ModelComponent)

    ModelComponent(Model &model)
        : m_model(model) {};

    Model &GetModel() { return this->m_model; }
    PROPERTY_GETTER(GetModel)

private:
    Model &m_model;
};
