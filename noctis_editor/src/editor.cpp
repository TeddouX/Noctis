#include "editor.hpp"

#include <engine/asset/asset_manager.hpp>


Editor Editor::s_instance;


Editor::Editor()
    : m_state(EditorState::PROJECT_SELECTION),
    m_window(800, 600, "Noctis Editor"), 
    m_ui(m_window, NOCTIS_OPENGL_VERSION)
{
}


Editor &Editor::GetInstance()
{
    return s_instance;
}


void Editor::Run()
{
    while (!this->m_window.ShouldClose())
    {
        glfwPollEvents();

        this->m_ui.Render();
        this->m_window.PostRender();
    }
}
