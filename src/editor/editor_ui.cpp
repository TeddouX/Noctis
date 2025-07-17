#include "editor_ui.hpp"


EditorUI::EditorUI(Window &window, const std::string &glslVers)
    : m_mainWindow(window)
{
    LOG_INFO("Initializing editor UI.")

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

    // Add all widgets
    m_allWidgets.push_back(std::make_unique<SceneDisplayWidget>(this->m_mainWindow));
    m_allWidgets.push_back(std::make_unique<ActorPropertiesWidget>());
    m_allWidgets.push_back(std::make_unique<AssetExplorerWidget>());
    m_allWidgets.push_back(std::make_unique<ConsoleWidget>());
    m_allWidgets.push_back(std::make_unique<SceneTreeWidget>());
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
            // Do nothing for now
            if (ImGui::MenuItem("Create Scene")) true;
            
            if (ImGui::MenuItem("Save Scene", "Ctrl+S"))
                SCENE_MANAGER().SaveCurrScene();

            ImGui::EndMenu();
        }

        ImGui::EndMainMenuBar();
    }
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
    }
}


void EditorUI::Render()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    this->DockDisplays();

    // ImGui::ShowDemoWindow();

    this->ShowMenuBar();
    this->HandleInput();

    // Update all widgets
    for (std::unique_ptr<IWidget> &widget : this->m_allWidgets)
    {
        widget->Update();
        widget->Render();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
