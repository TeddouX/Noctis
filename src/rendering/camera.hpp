#pragma once
#include "shader.hpp"
#include "../core/math/math.hpp"


namespace Math = UnE::Math;


class Camera 
{
public:
    Camera();
    Camera(Vec3 pos, float aspectRatio, float fov, float near, float far);

    inline float GetAspect() const { return this->m_aspectRatio; }
    void         Resize(float aspectRatio);

    Vec3 GetForwardVec() const;
	Mat4 GetViewMatrix() const;
	Mat4 GetProjectionMatrix() const;
    void SetShaderMatrices(Shader& shader) const;

    inline const Vec3 &GetPosition() const { return this->m_position; }
    inline const void  SetPosition(const Vec3 &pos) { this->m_position = pos; }

private:
    Vec3  m_position;
    float m_aspectRatio;
    float m_near, m_far;
	float m_fov;
	float m_yaw = 0.f, m_pitch = 0.f;
};
