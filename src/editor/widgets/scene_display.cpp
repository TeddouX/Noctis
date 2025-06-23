#include "scene_display.hpp"

// ONLY FOR TESTING
#include "../../rendering/model.hpp"
#include "../../rendering/renderer.hpp"
#include "../../loading/model_loader.hpp"


// ONLY FOR TESTING
std::shared_ptr<Model> model;
std::shared_ptr<Shader> shader;

SceneDisplayWidget::SceneDisplayWidget()
{
    // ONLY FOR TESTING
    model = ModelLoader::LoadModel("./monkey.obj");
    shader = std::make_shared<Shader>("./src/rendering/shaders/default.vert", "./src/rendering/shaders/default.frag");
}


void SceneDisplayWidget::Render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(
        std::string(SceneDisplayWidget::name).c_str(), 
        nullptr, 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
    );
    ImVec2 windowSize{ ImGui::GetWindowSize() };

    this->m_frameBuffer.Bind();

    // ONLY FOR TESTING
    Renderer::SetActiveShader(shader);
    Renderer::RenderModel(60, windowSize.x / windowSize.y, 0.01f, 1000, *model);

    this->m_frameBuffer.Unbind();

    ImGui::Image(
        (ImTextureID)(intptr_t) this->m_frameBuffer.GetTextureID(), 
        ImVec2{ static_cast<float>(this->m_frameBuffer.width), static_cast<float>(this->m_frameBuffer.height) },
        ImVec2{ 0.f, 1.f },  
        ImVec2{ 1.f, 0.f }
    );

    // Resize frame buffer if needed
    if (this->m_frameBuffer.width != static_cast<int>(windowSize.x ) 
     || this->m_frameBuffer.height != static_cast<int>(windowSize.y))
        this->m_frameBuffer.Resize(static_cast<int>(windowSize.x), static_cast<int>(windowSize.y));

 
    ImGui::End();
    ImGui::PopStyleVar();
}
