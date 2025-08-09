#include "editor.hpp"


Editor Editor::s_instance;


Editor::Editor()
    : m_state(EditorState::PROJECT_SELECTION),
    m_window(800, 600, "Unknown Engine"), 
    m_ui(m_window, GLSL_VERS)
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
