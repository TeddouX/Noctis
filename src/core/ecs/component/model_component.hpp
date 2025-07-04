#pragma once
#include <memory>

#include "../../../rendering/model.hpp"


// A ModelComponent stores a pointer to a model that can be rendered
struct ModelComponent
{
    std::shared_ptr<Model> model;
};
