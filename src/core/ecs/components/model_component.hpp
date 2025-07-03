#pragma once
#include <memory>

#include "../../../rendering/model.hpp"


struct ModelComponent
{
    std::shared_ptr<Model> model;
};
