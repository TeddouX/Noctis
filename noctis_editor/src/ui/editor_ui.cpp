#include "editor_ui.hpp"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <noctis/window.hpp>

#include "../utils/imgui_utils.hpp"
#include "../editor.hpp"
#include "widget/scene_display.hpp"
#include "widget/scene_tree.hpp"
#include "widget/asset_explorer.hpp"
#include "widget/properties.hpp"
#include "widget/console.hpp"
#include "widget/widget.hpp"

namespace NoctisEditor
{

EditorUI::EditorUI(std::shared_ptr<Noctis::Window> window, const char *glslVers)
    : m_mainWindow(window)
{
    LOG_INFO("Initializing editor UI.");

    GLFWwindow* glfwWindow = window->GetWindow();
    
    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVers);
    
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.IniFilename = nullptr;
    io.FontDefault = io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\Roboto-Regular.ttf", 
        18.0f, 
        nullptr, 
        io.Fonts->GetGlyphRangesDefault()
    );

    ImGuiStyle &style = ImGui::GetStyle();
    style.FrameRounding = 3;
    style.FrameBorderSize = 1;
    style.WindowMenuButtonPosition = ImGuiDir_None;
    style.WindowRounding = 3;

    // Add all widgets
    auto propertiesWidget = std::make_shared<PropertiesWidget>();

    m_allWidgets.push_back(std::make_shared<SceneDisplayWidget>(this->m_mainWindow));
    m_allWidgets.push_back(std::make_shared<AssetExplorerWidget>(propertiesWidget));
    m_allWidgets.push_back(std::make_shared<ConsoleWidget>());
    m_allWidgets.push_back(std::make_shared<SceneTreeWidget>());
    m_allWidgets.push_back(propertiesWidget);
}


void EditorUI::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // ImGui::ShowDemoWindow();
    
    this->DockDisplays();

    // Handle input from the window
    this->HandleInput();

    // Show popups etc...
    this->HandleState();
    
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
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

        ImGuiID centerID          = dockspaceID;
        ImGuiID actorPropertiesID = ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Right, .25f, nullptr, &centerID);
        ImGuiID assetExplorerID   = ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Down, .3f, nullptr, &centerID);
        ImGuiID sceneTreeID       = ImGui::DockBuilderSplitNode(centerID, ImGuiDir_Left, .25f, nullptr, &centerID);

        ImGui::DockBuilderDockWindow(SceneDisplayWidget::GetName().c_str(), centerID);
        ImGui::DockBuilderDockWindow(PropertiesWidget::GetName().c_str(), actorPropertiesID);
        ImGui::DockBuilderDockWindow(AssetExplorerWidget::GetName().c_str(), assetExplorerID);
        ImGui::DockBuilderDockWindow(ConsoleWidget::GetName().c_str(), assetExplorerID);
        ImGui::DockBuilderDockWindow(SceneTreeWidget::GetName().c_str(), sceneTreeID);

        ImGui::DockBuilderFinish(dockspaceID);
    }
}


void EditorUI::ShowMenuBar()
{
    bool showCreateSceneModal = false;

    if (ImGui::BeginMainMenuBar()) 
    {
        if (ImGui::BeginMenu("Scene")) 
        {
            if (ImGui::MenuItem("Create Scene", "Ctrl+Shift+N"))
                showCreateSceneModal = true;

            Project *currProj = EDITOR().GetCurrProject();
            if (!currProj)
                return;

            SceneManager &sm = currProj->GetSceneManager();
            if (ImGui::BeginMenu("Load Scene"))
            {
                auto allScenes = sm.GetAllScenes();
                // Iterate through all the scenes to create a 
                // menu item for each one
                for (auto &[name, scenePtr] : allScenes)
                    if (ImGui::MenuItem(name.c_str()))
                        sm.SetCurrentScene(name);
                
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                sm.SaveCurrentScene();

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }

    if (showCreateSceneModal)
        ImGui::OpenPopup("Create Scene##EDITOR_POPUP");
}


void EditorUI::HandleState()
{
    this->ShowCreateSceneModal();

    // Handle the editor state
    EditorState state = EDITOR().GetState();
    if (state == EditorState::PROJECT_SELECTION)
    {
        this->m_mainWindow->SetResizable(false);
        this->m_psUI.Render();
    }
    else if (state == EditorState::IN_EDITOR)
    {
        this->m_mainWindow->SetResizable(true);

        // Show the menu on top of the window
        this->ShowMenuBar();

        // Update all widgets
        for (std::shared_ptr<IWidget> &widget : this->m_allWidgets)
        {
            widget->Update();
            widget->Render();
        }
    }
}


// Input from the glfw window
void EditorUI::HandleInput()
{
    ImGuiIO& io = ImGui::GetIO();

    // Prevent ImGui from capturing mouse 
    // input when the cursor is disabled
    if (this->m_mainWindow->IsCursorEnabled()) 
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
    else 
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;

        
    std::optional<Noctis::KeyCombo> optCombo = this->m_mainWindow->GetLastCombo(); 
    if (optCombo.has_value())
    {
        Noctis::KeyCombo combo = optCombo.value();

        Project *currProj = EDITOR().GetCurrProject();
        if (!currProj)
            return;

        SceneManager &sm = currProj->GetSceneManager();

        // Ctrl+S
        if (combo.Is(GLFW_KEY_S, { GLFW_MOD_CONTROL }))
            sm.SaveCurrentScene();

        // Ctrl+Shift+N
        if (combo.Is(GLFW_KEY_N, { GLFW_MOD_CONTROL, GLFW_MOD_SHIFT }))
            ImGui::OpenPopup("Create Scene##EDITOR_POPUP");
    }
}


void EditorUI::ShowCreateSceneModal()
{
    ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal("Create Scene##EDITOR_POPUP", nullptr, ImGuiWindowFlags_AlwaysAutoResize))
    {
        static std::string sceneName;

        ImGui::Separator();
        NoctisEditor::ResizableInputText("Scene name", sceneName, false);

        if (ImGui::Button("OK", ImVec2(120, 0))) 
        {
            SceneManager &sm = EDITOR().GetCurrProject()->GetSceneManager();
            
            sm.CreateScene(sceneName);
            sm.SetCurrentScene(sceneName);

            sceneName.clear();

            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            sceneName.clear();

            ImGui::CloseCurrentPopup(); 
        }
        
        ImGui::EndPopup();
    }
}

}
