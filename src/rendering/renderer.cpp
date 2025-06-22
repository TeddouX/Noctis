#include "renderer.hpp"


void Renderer::RenderModel(float fov, float aspectRatio, float near, float far, Model &model)
{
    glm::mat4 projectionMat = glm::perspective(glm::radians(fov), aspectRatio, near, far);
    // Maybe pass this as an argument (easier)
    glm::mat4 viewMat = glm::lookAt(glm::vec3(-3, 0, 0), glm::vec3(0), glm::vec3(0, 1, 0));

    if (!activeShader)
    {
        std::cout << "[ERROR]: Can't render a model without the current shader set." << std::endl;
        return;
    }

    // Set matrices
    Renderer::activeShader->Use();
    Renderer::activeShader->SetMatrix("Projection", projectionMat);
    Renderer::activeShader->SetMatrix("View", viewMat);
    model.Render(*Renderer::activeShader); // Render the mesh
}


void Renderer::SetActiveShader(std::shared_ptr<Shader> shader)
{
    Renderer::activeShader = shader;
}
