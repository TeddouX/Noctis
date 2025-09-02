#include "editor.hpp"

namespace NoctisEditor
{

Editor Editor::s_instance;

Editor::Editor()
    : m_state(EditorState::PROJECT_SELECTION),
    m_window(std::make_shared<Noctis::Window>(800, 600, "Noctis Editor")), 
    m_ui(m_window, NOCTIS_OPENGL_VERSION)
{
}

Editor &Editor::GetInstance()
{
    return s_instance;
}

void Editor::Run()
{
    while (!m_window->ShouldClose())
    {
        glfwPollEvents();

        m_ui.Render();
        m_window->PostRender();
    }
}

}
