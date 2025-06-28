#pragma once
#include <vector>
#include <memory>
#include <glm/glm.hpp>

#include "../../rendering/model.hpp"


struct ModelComponent
{
    std::shared_ptr<Model> model;
};

struct TransformComponent
{
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;
};
