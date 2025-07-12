#include "core/window.hpp"
#include "core/project.hpp"
#include "editor/editor_ui.hpp"
#include "core/filesystem.hpp"


int main() 
{
    Window window(800, 600, "Unknown Engine");

    fs::path projPath = fs::absolute("test_project");
    Project::Init(projPath);

    EditorUI ui(window, "#version 430 core");

    // LOG_WARN("This is a warning.");
    // LOG_ERR("This is an error.");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }
}

