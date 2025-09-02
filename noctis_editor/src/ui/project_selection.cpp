#include <sstream>
#include <imgui.h>
#include <imgui_internal.h>

#include "project_selection.hpp"
#include "../editor.hpp"
#include "../project.hpp"
#include "../utils/imgui_utils.hpp"

namespace NoctisEditor
{

void ProjectSelectionUI::Render()
{
    // Create an imgui window that fills all of the os window
    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->WorkPos);
    ImGui::SetNextWindowSize(viewport->WorkSize);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGuiWindowFlags wndFlags = ImGuiWindowFlags_NoDecoration 
        | ImGuiWindowFlags_NoResize;

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
    ImGui::Begin("Project Selection", nullptr, wndFlags);

    const char *selectProjButton = "Select Project";
    float buttonWidth = 180.f;

    // Calculate center offsets
    float offsetX = (ImGui::GetContentRegionAvail().x - buttonWidth) * .5f;
    float offsetY = (ImGui::GetContentRegionAvail().y - ImGui::CalcTextSize(selectProjButton).y) * .5f;

    // Center button
    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);
    bool pressed = ImGui::Button(selectProjButton, ImVec2(buttonWidth, 0.f));

    if (pressed)
    {
        fs::path projectPath = Noctis::Filesystem::FolderSelectDialog("%USERPROFILE%", "Select project folder");

        this->LoadProjectFolder(projectPath);
    }


    const char *createProjButton = "Create Project";

    // Update offset for the new button and add 
    // all the paddings for accuracy
    ImGuiStyle style = ImGui::GetStyle();
    offsetY = ImGui::CalcTextSize(createProjButton).y 
        + style.WindowPadding.y
        + style.FramePadding.y;

    ImGui::SetCursorPosX(ImGui::GetCursorPosX() + offsetX);
    ImGui::SetCursorPosY(ImGui::GetCursorPosY() + offsetY);
    pressed = ImGui::Button(createProjButton, ImVec2(buttonWidth, 0.f));

    if (pressed)
    {
        fs::path projectPath = Noctis::Filesystem::FolderSelectDialog("%USERPROFILE%", "Select project folder");
        
        this->CreateProjectFolder(projectPath);
    }

    ImGui::End();
    ImGui::PopStyleVar();
}


void ProjectSelectionUI::LoadProjectFolder(const fs::path &folder)
{
    if (Project::IsValidProjectFolder(folder))
        this->LoadProject(folder, "", false);
    else
        LOG_ERR("Folder {} is not a valid project folder.", folder.string());
}


void ProjectSelectionUI::CreateProjectFolder(const fs::path &folder)
{
    if (folder.empty())
        return;

    // Change this to a modal
    std::string projName = "My Project";

    // Append project name to the end 
    // of the selected path
    fs::path fullPath = folder / (projName + "\\");

    if (!fs::exists(fullPath))
    {
        // Create all directories in the project path
        fs::create_directories(fullPath);

        this->LoadProject(fullPath, projName, true);
    }
    else if (fs::is_empty(fullPath))
        this->LoadProject(fullPath, projName, true);
    else
        LOG_ERR("Project folder: {} is not empty.", fullPath.string());

}


void ProjectSelectionUI::LoadProject(const fs::path &folder, const std::string &name, bool firstTime)
{
    auto project = std::make_unique<Project>(folder, name);
    
    if (!project->Load(firstTime))
    {
        LOG_ERR("Project {} couldn't be loaded. See errors in console.", folder.string());
        return;
    }

    EDITOR().SetCurrProject(std::move(project));
    EDITOR().SetState(EditorState::IN_EDITOR);
}

}
