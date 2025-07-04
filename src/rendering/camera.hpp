#pragma once
#include <glm/gtc/matrix_transform.hpp>

#include "shader.hpp"


class Camera 
{
public:
    Camera();
    Camera(glm::vec3 pos, glm::vec2 viewSize, float fov, float near, float far);


    inline const glm::vec2 &GetSize() const { return this->m_size; }
    void      Resize(glm::vec2 viewSize);

    glm::vec3 GetForwardVec() const;
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjectionMatrix() const;
    void      SetShaderMatrices(Shader& shader) const;



private:
    glm::vec3 m_position;
    glm::vec2 m_size;
    float     m_near, m_far;
	float     m_fov;
	float     m_yaw = 0.f, m_pitch = 0.f;
};
