#include "scene_display.hpp"

// ONLY FOR TESTING
#include "../../core/scene/scene.hpp"
#include "../../core/scene/scene_manager.hpp"


// ONLY FOR TESTING
Scene scene("HelloWorld");

SceneDisplayWidget::SceneDisplayWidget()
{
    // TESTING
    SCENE_MANAGER().AddScene(&scene);
    SCENE_MANAGER().SetCurrScene(scene.GetName());
}


void SceneDisplayWidget::Render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(
        std::string(SceneDisplayWidget::name).c_str(), 
        nullptr, 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
    );
    ImVec2 sceneDisplaySize(ImGui::GetWindowSize());
    ImVec2 windowSize(ImGui::GetIO().DisplaySize);

    // If the window is not minimized
    if (!(windowSize.x == 0 || windowSize.y == 0))
    {
        // Resize camera view size if needed
        if (this->m_camera.GetSize().x != sceneDisplaySize.x || this->m_camera.GetSize().y != sceneDisplaySize.y)
            this->m_camera.Resize(glm::vec2(
                sceneDisplaySize.x, 
                sceneDisplaySize.y
            ));

        this->m_frameBuffer.Bind();

        glClearColor(.09f, .09f, .09f, 1.f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        scene.GetSystem<RenderSystem>()->SetCamera(&this->m_camera);
        scene.UpdateSystem<RenderSystem>(.0f);

        this->m_frameBuffer.Unbind();

        ImGui::Image(
            (ImTextureID)(intptr_t) this->m_frameBuffer.GetTextureID(), 
            ImVec2((float)this->m_frameBuffer.GetSize().x, (float)this->m_frameBuffer.GetSize().y),
            ImVec2(0.f, 1.f),  
            ImVec2(1.f, 0.f)
        );

        // Resize frame buffer if needed
        if (this->m_frameBuffer.GetSize().x != windowSize.x || this->m_frameBuffer.GetSize().y != windowSize.y)
            this->m_frameBuffer.Resize(glm::ivec2(
                (int)windowSize.x, 
                (int)windowSize.y
            ));
    }
 
    ImGui::End();
    ImGui::PopStyleVar();
}
