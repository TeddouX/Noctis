#pragma once
#include <noctis/filesystem.hpp>

namespace NoctisEditor
{

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
    void LoadProject(const fs::path &folder, const std::string &name, bool firstTime);
};

}
