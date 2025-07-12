#include "math.hpp"


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

Mat4 PerspectiveProjMatrix(float fov, float aspect, float near, float far)
{
    return glm::perspective(fov, aspect, near, far);
}

Vec3 Normalize(Vec3 vec) { return glm::normalize(vec); }

float *GetPtr(Mat4 mat) { return &(mat[0].x); }

float Radians(float degrees) { return glm::radians(degrees); }


namespace glm
{
  
void from_json(const json &j, Vec3 &vec3)
{
    j.at("x").get_to(vec3.x);
    j.at("y").get_to(vec3.y);
    j.at("z").get_to(vec3.z);
}

void to_json(json &j, const Vec3 &vec3)
{
    j = json{
        {"x", vec3.x},
        {"y", vec3.y},
        {"z", vec3.z}
    };
}

}
