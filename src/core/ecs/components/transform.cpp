#include "transform.hpp"


glm::mat4 Transform::GetModelMatrix() const
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