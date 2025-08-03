#pragma once
#include <sstream>
#include <imgui.h>
#include <imgui_internal.h>

#include <engine/filesystem.hpp>

#include "imgui_utils.hpp"
#include "../project.hpp"


class ProjectSelectionUI
{
public:
    ProjectSelectionUI() = default;

    void Render();

private:
    void CreateProjectFolder(const fs::path &folder);
    void LoadProjectFolder(const fs::path &folder);

    /// @brief Loads all the project's scenes and assets
    /// and sets it as the current project in the editor
    void LoadProject(const fs::path &folder, bool firstTime);
};
