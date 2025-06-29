#include "camera.hpp"


Camera::Camera(glm::vec3 pos, float fov, float aspectRatio, float near, float far)
	: position(pos), m_fov(glm::radians(fov)), m_aspectRatio(aspectRatio), m_near(near), m_far(far)
{
}


glm::vec3 Camera::GetForwardVec() const
{
	glm::vec3 front(0.0f);

	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	return front;
}


glm::mat4 Camera::GetViewMatrix() const
{
	glm::vec3 cameraFront = glm::normalize(this->GetForwardVec());

	return glm::lookAt(this->position, this->position + cameraFront, glm::vec3(0, 1, 0));
}


glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(this->m_fov, this->m_aspectRatio, this->m_near, this->m_far);
}


void Camera::SetShaderMatrices(Shader& shader) const
{
	shader.SetMatrix("View",       this->GetViewMatrix());
	shader.SetMatrix("Projection", this->GetProjectionMatrix());
}
