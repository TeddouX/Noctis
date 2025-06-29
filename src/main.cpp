#include "core/window.hpp"
#include "editor/editor_ui.hpp"
#include "loading/model_loader.hpp"


int main() 
{
    Window window(800, 600, "Unknown Engine");
    EditorUI ui(window, "#version 330 core");

    LOG_WARN("This is a warning.");
    LOG_ERR("This is an error.");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }

    return 0;
}
