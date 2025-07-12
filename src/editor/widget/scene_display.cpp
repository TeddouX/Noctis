#include "scene_display.hpp"

SceneDisplayWidget::SceneDisplayWidget()
{
    // TESTING
    SCENE_MANAGER().AddScene("HelloWorld");
    SCENE_MANAGER().SetCurrScene("HelloWorld");
}


void SceneDisplayWidget::Render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(
        std::string(SceneDisplayWidget::name).c_str(), 
        nullptr, 
        ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse
    );
    ImVec2 windowSize = ImGui::GetIO().DisplaySize;
    ImVec2 availableSpace = ImGui::GetContentRegionAvail();

    static ImVec2 lastSize = availableSpace;

    // If the window is not minimized
    if (!(windowSize.x == 0 || windowSize.y == 0))
    {
        // Resize frame buffer if needed
        this->m_frameBuffer.Resize(IVec2(
            this->m_viewportWidth, 
            this->m_viewportHeight
        ));

        this->m_frameBuffer.Bind();

        if (availableSpace.x != lastSize.x || availableSpace.y != lastSize.y)
            this->UpdateViewport((int)availableSpace.x, (int)availableSpace.y);

        Scene *currScene = SCENE_MANAGER().GetCurrScene();
        currScene->GetSystem<RenderSystem>()->SetCamera(&this->m_camera);
        currScene->UpdateSystem<LightingSystem>(.0f);
        currScene->UpdateSystem<RenderSystem>(.0f);

        // TESTING
        currScene->Unload();

        this->m_frameBuffer.Unbind();

        ImGui::SetCursorPos(ImVec2(
            (float)this->m_viewportX, 
            (float)this->m_viewportY + ImGui::GetStyle().DisplayWindowPadding.y
        ));

        ImGui::Image(
            (ImTextureID)(intptr_t) this->m_frameBuffer.GetTextureID(), 
            ImVec2((float)this->m_viewportWidth, (float)this->m_viewportHeight),
            ImVec2(0.f, 1.f),  
            ImVec2(1.f, 0.f)
        );
    }

    lastSize = availableSpace;

    ImGui::End();
    ImGui::PopStyleVar();
}


void SceneDisplayWidget::UpdateViewport(int windowWidth, int windowHeight)
{
    float windowAspectRatio = (float)windowWidth / (float)windowHeight;
    
    // Resize viewport while keeping aspect ratio
    if (windowAspectRatio > this->m_aspectRatio) 
    {
        this->m_viewportHeight = windowHeight;
        this->m_viewportWidth = (int)(windowHeight * this->m_aspectRatio);
        this->m_viewportX = (windowWidth - this->m_viewportWidth) / 2;
        this->m_viewportY = 0;
    } 
    else 
    {
        this->m_viewportWidth = windowWidth;
        this->m_viewportHeight = (int)(windowWidth / this->m_aspectRatio);
        this->m_viewportX = 0;
        this->m_viewportY = (windowHeight - this->m_viewportHeight) / 2;
    }
    
    glViewport(0, 0, this->m_viewportWidth, this->m_viewportHeight);
}
