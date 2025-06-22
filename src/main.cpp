#include <cstdio>

#include "core/window.hpp"
#include "editor/editor_ui.hpp"
#include "loading/model_loader.hpp"


int main() 
{
    Window window(800, 600, "COUCOU");
    EditorUI ui(window, "#version 330 core");

    while (!window.ShouldClose())
    {
        ui.Render();
        
        window.PostRender();
    }

    return 0;
}
