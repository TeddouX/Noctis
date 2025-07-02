#pragma once
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include "../../rendering/model.hpp"


struct ModelComponent
{
    std::shared_ptr<Model> model;
};

class TransformComponent
{
public:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

    glm::mat4 GetModelMatrix() const
    {
        // Identity
        glm::mat4 model(1);

        // Translation
        model = glm::translate(model, this->pos);
        // Rotation
        glm::quat quaternion = glm::quat(glm::radians(this->rot));
        glm::mat4 rotationMatrix = glm::toMat4(quaternion);
        model *= rotationMatrix;
        // Scale
        model = glm::scale(model, this->scale);

        return model;
    }
};
