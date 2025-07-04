#include "camera.hpp"


Camera::Camera()
	: m_position(0, 0, 0), m_size(0, 0), m_fov(0.f), m_near(0.f), m_far(0.f)
{
}


Camera::Camera(glm::vec3 pos, glm::vec2 viewSize, float fov, float near, float far)
	: m_position(pos), m_size(viewSize),  m_fov(glm::radians(fov)), m_near(near), m_far(far)
{
}


void Camera::Resize(glm::vec2 viewSize)
{
	this->m_size = viewSize;
}


glm::vec3 Camera::GetForwardVec() const
{
	glm::vec3 front(0.f);

	front.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
	front.y = sin(glm::radians(m_pitch));
	front.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));

	return front;
}


glm::mat4 Camera::GetViewMatrix() const
{
	glm::vec3 cameraFront = glm::normalize(this->GetForwardVec());

	return glm::lookAt(this->m_position, this->m_position + cameraFront, glm::vec3(0, 1, 0));
}


glm::mat4 Camera::GetProjectionMatrix() const
{
	return glm::perspective(
		this->m_fov, 
		this->m_size.x / this->m_size.y, 
		this->m_near, 
		this->m_far
	);
}


void Camera::SetShaderMatrices(Shader& shader) const
{
	shader.SetMatrix("View",       this->GetViewMatrix());
	shader.SetMatrix("Projection", this->GetProjectionMatrix());
}
