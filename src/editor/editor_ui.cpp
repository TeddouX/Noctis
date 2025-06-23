#include <iostream>
#include <imgui_internal.h>

#include "editor_ui.hpp"
#include "../core/window.hpp"


EditorUI::EditorUI(Window &window, const std::string &glslVers)
{
    GLFWwindow* glfwWindow = window.GetWindow();
    this->m_imGuiScale = 1;

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVers.c_str());

    // Set the scale for all objects
    ImGuiStyle style = ImGui::GetStyle();
    style.ScaleAllSizes(this->m_imGuiScale);

    // Config ImGui
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Disable the imgui.ini file 
    io.IniFilename = NULL;
}


void EditorUI::DockDisplays() const
{
    ImGuiID dockspaceID = ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());

    // Only run on the first frame
    static bool firstTime = true;
    if (firstTime)
    {
        firstTime = false;    

        ImGui::DockBuilderRemoveNode(dockspaceID);
        ImGui::DockBuilderAddNode(dockspaceID);
        ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetMainViewport()->Size);

        ImGuiID centerID = dockspaceID;
        ImGuiID actorPropertiesID = ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Right, .25f, nullptr, &centerID);
        ImGuiID assetExplorerID = ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Down, .3f, nullptr, &centerID); 
        ImGuiID sceneTreeID = ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Left, .25f, nullptr, &centerID);

        ImGui::DockBuilderDockWindow(std::string(SceneDisplayWidget::name).c_str(), centerID);
        ImGui::DockBuilderDockWindow(std::string(ActorPropertiesWidget::name).c_str(), actorPropertiesID);
        ImGui::DockBuilderDockWindow(std::string(AssetExplorerWidget::name).c_str(), assetExplorerID);
        ImGui::DockBuilderDockWindow(std::string(SceneTreeWidget::name).c_str(), sceneTreeID);

        ImGui::DockBuilderFinish(dockspaceID);
    }
}


void EditorUI::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->DockDisplays();

    // ImGui::ShowDemoWindow();

    this->w.Render();
    this->w2.Render();
    this->w3.Render();
    this->w4.Render();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
