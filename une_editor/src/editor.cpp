#include "editor.hpp"


Editor::Editor()
    : m_state(EditorState::PROJECT_SELECTION),
    m_window(800, 600, "Unknown Engine"), 
    m_ui(m_window, GLSL_VERS)
{
}


void Editor::Init()
{
    LOG_INFO("Initializing editor.");

    m_instance = new Editor();
}


Editor *Editor::GetInstance()
{
    if (!m_instance)
    {
        LOG_ERR("Editor instance not initialized.");
        return nullptr;
    }

    return m_instance;
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
