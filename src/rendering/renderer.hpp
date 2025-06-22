#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "model.hpp"


class Renderer
{
public:
    static void RenderModel(float fov, float aspectRatio, float near, float far, Model &model);
    static void SetActiveShader(std::shared_ptr<Shader> shader);

private:
    inline static std::shared_ptr<Shader> activeShader;
};
