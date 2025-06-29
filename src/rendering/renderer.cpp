#include "renderer.hpp"


void Renderer::RenderModel(const Model &model, const TransformComponent &transform)
{
    if (!activeShader)
    {
        std::cout << "[ERROR]: Can't render a model without the current shader set." << std::endl;
        return;
    }

    if (!activeCamera)
    {
        std::cout << "[ERROR]: Can't render a model without the current camera set." << std::endl;
        return;
    }

    // Set matrices
    Renderer::activeShader->Use();
    Renderer::activeShader->SetMatrix("Model", transform.GetModelMatrix());
    Renderer::activeCamera->SetShaderMatrices(*Renderer::activeShader);
    model.Render(*Renderer::activeShader);
}


void Renderer::SetActiveCamera(std::shared_ptr<Camera> camera)
{
    Renderer::activeCamera = camera;
}


void Renderer::SetActiveShader(std::shared_ptr<Shader> shader)
{
    Renderer::activeShader = shader;
}
