#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"


class Camera 
{
public:
    Camera(glm::vec3 pos, float fov, float aspectRatio, float near, float far);

    glm::vec3 position;

    glm::vec3 GetForwardVec() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
    void SetMatrices(Shader& shader) const;

private:
    float m_near, m_far;
	float m_fov;
	float m_aspectRatio;
	float m_yaw = 0.0f, m_pitch = 0.0f;
};
