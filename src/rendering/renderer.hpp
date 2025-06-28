#pragma once
#include <memory>
#include <glm/glm.hpp>

#include "model.hpp"
#include "shader.hpp"
#include "camera.hpp"
#include "../core/ecs/all_components.hpp"


class Renderer
{
public:
    static void RenderModel(const Model &model, const TransformComponent &transform);
    static void SetActiveShader(std::shared_ptr<Shader> shader);
    static void SetActiveCamera(std::shared_ptr<Camera> camera);

private:
    inline static std::shared_ptr<Shader> activeShader;
    inline static std::shared_ptr<Camera> activeCamera;
};
