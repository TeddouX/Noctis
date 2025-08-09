#pragma once
#include "shader.hpp"
#include "ssbo.hpp"
#include "../math/math.hpp"


class NOCTIS_API Camera 
{
public:
    struct Data
    {
        Mat4 projectionMatrix;
        Mat4 viewMatrix;
        Vec4 pos;
    };

    Camera(Vec3 pos, float aspectRatio, float fov, float nearDst, float farDst);

    float GetAspect() const { return this->m_aspectRatio; }
    void  Resize(float aspectRatio);

    void RotateBy(float yaw, float pitch);

    Vec3 GetForwardVec() const;
	Mat4 GetViewMatrix() const;
	Mat4 GetProjectionMatrix() const;
    void UploadData();

    inline const Vec3 &GetPosition() const { return this->m_position; }
    inline const void  SetPosition(const Vec3 &pos) { this->m_position = pos; }

private:
    Vec3  m_position;
    float m_aspectRatio;
    float m_near, m_far;
    float m_fov;
    float m_yaw = 0.f, m_pitch = 0.f;

    SSBO<Camera::Data> m_cameraSSBO = SSBO<Camera::Data>(0);
};
