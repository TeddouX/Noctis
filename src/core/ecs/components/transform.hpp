#pragma once
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>


class Transform
{
public:
    glm::vec3 pos;
    glm::vec3 rot;
    glm::vec3 scale;

    glm::mat4 GetModelMatrix() const;
};
