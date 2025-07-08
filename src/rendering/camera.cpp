#include "camera.hpp"


Camera::Camera()
	: m_position(0, 0, 0), m_aspectRatio(0.f), m_fov(0.f), m_near(0.f), m_far(0.f)
{
	this->Init();
}


Camera::Camera(Vec3 pos, float aspectRatio, float fov, float near, float far)
	: m_position(pos), m_aspectRatio(aspectRatio),  m_fov(glm::radians(fov)), m_near(near), m_far(far)
{
	this->Init();
}

void Camera::Init()
{
	this->m_cameraSSBO.BindToPoint(0);
}


void Camera::Resize(float aspectRatio)
{
	this->m_aspectRatio = aspectRatio;
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
		this->m_aspectRatio, 
		this->m_near, 
		this->m_far
	);
}


void Camera::SetShaderMatrices(Shader& shader, Mat4 modelMatrix)
{
	CameraData data;
	data.modelMatrix = modelMatrix;
	data.viewMatrix = this->GetViewMatrix();
	data.projectionMatrix = this->GetProjectionMatrix();

	this->m_cameraSSBO.UploadData(data);
}
