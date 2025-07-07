#include "math.hpp"


namespace UnE::Math
{
    Mat4 ModelMatrix(Vec3 pos, Vec3 rot, Vec3 scale)
    {
        // Identity
        Mat4 model(1);

        // Translation
        model = glm::translate(model, pos);
        // Rotation
        Quaternion quaternion(glm::radians(rot));
        Mat4 rotationMatrix = glm::toMat4(quaternion);
        model *= rotationMatrix;
        // Scale
        model = glm::scale(model, scale);

        return model;
    }

    Mat4 ViewMatrix(Vec3 pos, Vec3 front)
    {
        return ViewMatrix(pos, front, Vec3(0, 1, 0));
    }

    Mat4 ViewMatrix(Vec3 pos, Vec3 front, Vec3 up)
    {
        return glm::lookAt(pos, pos + front, up);
    }

    Mat4 PerspectiveProjMatrix(float fov, Vec2 size, float near, float far)
    {
        return glm::perspective(fov, size.x / size.y, near, far);
    }
    
    Vec3 Normalize(Vec3 vec) { return glm::normalize(vec); }

    float *GetPtr(Mat4 mat) { return glm::value_ptr(mat); }

    float Radians(float degrees) { return glm::radians(degrees); }
}