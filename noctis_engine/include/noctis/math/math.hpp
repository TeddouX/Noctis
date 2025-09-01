#pragma once
#include <nlohmann/json.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp> 
#include <glm/gtc/matrix_transform.hpp>

#include "../engine.hpp"

using json = nlohmann::json;

namespace Noctis
{

using Vec2 = glm::vec2;
using IVec2 = glm::ivec2;
using Vec3 = glm::vec3;
using Vec4 = glm::vec4;
using Mat4 = glm::mat4;
using Quaternion = glm::quat;


NOCTIS_API Mat4 ModelMatrix(Vec3 pos, Vec3 rot, Vec3 scale);
NOCTIS_API Mat4 ViewMatrix(Vec3 pos, Vec3 front);
NOCTIS_API Mat4 ViewMatrix(Vec3 pos, Vec3 front, Vec3 up);
NOCTIS_API Mat4 PerspectiveProjMatrix(float fov, float aspect, float near, float far);

NOCTIS_API Vec3 Normalize(Vec3 vec);

NOCTIS_API float *GetPtr(Mat4 mat);

NOCTIS_API float Radians(float degrees);

}

// Serialization
namespace glm
{

void from_json(const json &j, Noctis::Vec3 &vec3);
void to_json(json &j, const Noctis::Vec3 &vec3);

}
