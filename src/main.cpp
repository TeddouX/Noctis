#include "core/window.hpp"
#include "core/project.hpp"
#include "core/filesystem.hpp"
#include "editor/editor_ui.hpp"


int main() 
{
    // This will need to be moved to some kind of 
    // editor_application.cpp

    Window window(800, 600, "Unknown Engine");

    // TESTING
    fs::path projPath = fs::absolute("test_project");
    Project::Init(projPath);

    EditorUI ui(window, "#version 430 core");

    // LOG_WARN("This is a warning.");
    // LOG_ERR("This is an error.");

    while (!window.ShouldClose())
    {
        glfwPollEvents();
        
        ui.Render();
        
        window.PostRender();
    }
}

