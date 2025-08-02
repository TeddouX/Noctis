#include "ui/editor_ui.hpp"
#include "editor.hpp"


EditorUI::EditorUI(Window &window, const char *glslVers)
    : m_mainWindow(window)
{
    LOG_INFO("Initializing editor UI.")

    GLFWwindow* glfwWindow = window.GetWindow();
    this->m_imGuiScale = 2;

    // Init ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(glfwWindow, true);
    ImGui_ImplOpenGL3_Init(glslVers);

    // Set the scale for all objects
    ImGuiStyle style = ImGui::GetStyle();
    style.ScaleAllSizes(this->m_imGuiScale);

    // Config ImGui
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    // Disable the imgui.ini file 
    io.IniFilename = NULL;

    // Add all widgets
    m_allWidgets.push_back(std::make_shared<SceneDisplayWidget>(this->m_mainWindow));
    m_allWidgets.push_back(std::make_shared<ActorPropertiesWidget>());
    m_allWidgets.push_back(std::make_shared<AssetExplorerWidget>());
    m_allWidgets.push_back(std::make_shared<ConsoleWidget>());
    m_allWidgets.push_back(std::make_shared<SceneTreeWidget>());
}


void EditorUI::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    
    ImGui::ShowDemoWindow();
    
    this->DockDisplays();

    // Handle input from the window
    this->HandleInput();

    // Show popups etc...
    this->HandleState();

    EditorState state = EDITOR()->GetState();
    if (state == EditorState::PROJECT_SELECTION)
    {
        // blablabla
    }
    else if (state == EditorState::IN_EDITOR)
    {
        // Show the menu on top of the window
        this->ShowMenuBar();

        // Update all widgets
        for (std::shared_ptr<IWidget> &widget : this->m_allWidgets)
        {
            widget->Update();
            widget->Render();
        }
    }
    
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

        ImGui::DockBuilderDockWindow(std::string(SceneDisplayWidget::name).c_str(), centerID);
        ImGui::DockBuilderDockWindow(std::string(ActorPropertiesWidget::name).c_str(), actorPropertiesID);
        ImGui::DockBuilderDockWindow(std::string(AssetExplorerWidget::name).c_str(), assetExplorerID);
        ImGui::DockBuilderDockWindow(std::string(ConsoleWidget::name).c_str(), assetExplorerID);
        ImGui::DockBuilderDockWindow(std::string(SceneTreeWidget::name).c_str(), sceneTreeID);

        ImGui::DockBuilderFinish(dockspaceID);
    }
}


void EditorUI::ShowMenuBar()
{
    if (ImGui::BeginMainMenuBar()) 
    {
        if (ImGui::BeginMenu("Scene")) 
        {
            if (ImGui::MenuItem("Create Scene", "Ctrl+Shift+N"))
                this->m_state.showCreateScenePopup = true;

            if (ImGui::BeginMenu("Load Scene"))
            {
                auto &allScenes = SCENE_MANAGER().GetAllScenes();
                // Iterate through all the scenes to create a 
                // menu item for each one
                for (auto &[name, scenePtr] : allScenes)
                    if (ImGui::MenuItem(name.c_str()))
                        SCENE_MANAGER().SetCurrScene(name);
                
                ImGui::EndMenu();
            }

            if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                SCENE_MANAGER().SaveCurrScene();

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
}


void EditorUI::HandleState()
{
    if (this->m_state.showCreateScenePopup)
    {
        ImGui::OpenPopup("Create Scene##EDITOR_POPUP");
        this->m_state.showCreateScenePopup = false;
    }

    this->ShowCreateSceneModal();
}


// Input from the glfw window
void EditorUI::HandleInput()
{
    ImGuiIO& io = ImGui::GetIO();

    // Prevent ImGui from capturing mouse 
    // input when the cursor is disabled
    if (this->m_mainWindow.IsCursorEnabled()) 
        io.ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
    else 
        io.ConfigFlags |= ImGuiConfigFlags_NoMouse;

        
    std::optional<KeyCombo> optCombo = this->m_mainWindow.GetLastCombo(); 
    if (optCombo.has_value())
    {
        KeyCombo combo = optCombo.value();
        
        // Ctrl+S
        if (combo.Is(GLFW_KEY_S, { GLFW_MOD_CONTROL }))
            SCENE_MANAGER().SaveCurrScene();

        // Ctrl+Shift+N
        if (combo.Is(GLFW_KEY_N, { GLFW_MOD_CONTROL, GLFW_MOD_SHIFT }))
            this->m_state.showCreateScenePopup = true;
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
        ImGui::ResizableInputText("Scene name", sceneName, false);

        if (ImGui::Button("OK", ImVec2(120, 0))) 
        { 
            ImGui::CloseCurrentPopup();
            SCENE_MANAGER().AddScene(sceneName);
            SCENE_MANAGER().SetCurrScene(sceneName);
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0))) 
            ImGui::CloseCurrentPopup(); 
        
        ImGui::EndPopup();
    }
}
