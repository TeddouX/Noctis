#include "camera.hpp"


Camera::Camera()
	: m_position(0, 0, 0), m_size(0, 0), m_fov(0.f), m_near(0.f), m_far(0.f)
{
}


Camera::Camera(Vec3 pos, Vec2 viewSize, float fov, float near, float far)
	: m_position(pos), m_size(viewSize),  m_fov(glm::radians(fov)), m_near(near), m_far(far)
{
}


void Camera::Resize(Vec2 viewSize)
{
	this->m_size = viewSize;
}


Vec3 Camera::GetForwardVec() const
{
	Vec3 front(0.f);

	front.x = cos(Math::Radians(m_yaw)) * cos(Math::Radians(m_pitch));
	front.y = sin(Math::Radians(m_pitch));
	front.z = sin(Math::Radians(m_yaw)) * cos(Math::Radians(m_pitch));

	return front;
}


Mat4 Camera::GetViewMatrix() const
{
	Vec3 cameraFront = Math::Normalize(this->GetForwardVec());

	return Math::ViewMatrix(this->m_position, cameraFront);
}


Mat4 Camera::GetProjectionMatrix() const
{
	return Math::PerspectiveProjMatrix(
		this->m_fov, 
		this->m_size, 
		this->m_near, 
		this->m_far
	);
}


void Camera::SetShaderMatrices(Shader& shader) const
{
	shader.SetMatrix("View",       this->GetViewMatrix());
	shader.SetMatrix("Projection", this->GetProjectionMatrix());
}
