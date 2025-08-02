#include <editor_ui.hpp>
#include <engine/window.hpp>
#include <engine/project.hpp>
#include <engine/filesystem.hpp>


int main()
{
    Window window(800, 600, "Unknown Engine");

    // TESTING
    fs::path projPath = fs::absolute("test_project");
    Project::Init(projPath);

    EditorUI ui(window, "#version 430 core");

    while (!window.ShouldClose())
    {
        glfwPollEvents();
        
        ui.Render();
        
        window.PostRender();
    }
    
    return 0;
}