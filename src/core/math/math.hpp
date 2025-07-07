#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp>


using Vec3 = glm::vec3;
using Vec2 = glm::vec2;
using IVec2 = glm::ivec2;
using Mat4 = glm::mat4;
using Quaternion = glm::quat;


namespace UnE::Math
{
    Mat4 ModelMatrix(Vec3 pos, Vec3 rot, Vec3 scale);
    Mat4 ViewMatrix(Vec3 pos, Vec3 front);
    Mat4 ViewMatrix(Vec3 pos, Vec3 front, Vec3 up);
    Mat4 PerspectiveProjMatrix(float fov, Vec2 size, float near, float far);

    Vec3 Normalize(Vec3 vec);

    float *GetPtr(Mat4 mat);

    float Radians(float degrees);
}