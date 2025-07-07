#pragma once
#include "shader.hpp"
#include "../core/math/math.hpp"


namespace Math = UnE::Math;


class Camera 
{
public:
    Camera();
    Camera(Vec3 pos, Vec2 viewSize, float fov, float near, float far);


    inline const Vec2 &GetSize() const { return this->m_size; }
    void      Resize(Vec2 viewSize);

    Vec3 GetForwardVec() const;
	Mat4 GetViewMatrix() const;
	Mat4 GetProjectionMatrix() const;
    void SetShaderMatrices(Shader& shader) const;



private:
    Vec3 m_position;
    Vec2 m_size;
    float     m_near, m_far;
	float     m_fov;
	float     m_yaw = 0.f, m_pitch = 0.f;
};
