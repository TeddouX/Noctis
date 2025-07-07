#include "core/window.hpp"
#include "core/project.hpp"
#include "editor/editor_ui.hpp"


int main() 
{
    Window window(800, 600, "Unknown Engine");

    std::string projPath = std::filesystem::absolute("test_project").string();
    Project::Init(projPath);

    EditorUI ui(window, "#version 330 core");

    // LOG_WARN("This is a warning.");
    // LOG_ERR("This is an error.");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }

    return 0;
}

