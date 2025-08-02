#pragma once
#include <engine/window.hpp>

#include "project.hpp"
#include "ui/editor_ui.hpp"


#define EDITOR() Editor::GetInstance()

#define GLSL_VERS "#version 430 core"


enum class EditorState
{
    PROJECT_SELECTION,
    IN_EDITOR
};


class EditorUI;


class Editor
{
public:
    static void    Init();
    static Editor *GetInstance();

    EditorState GetState() const { return this->m_state; }
    void SetState(EditorState state) { this->m_state = state; }

    Project *GetCurrProject() { return this->m_currProject; }
    void SetCurrProject(Project *project) { this->m_currProject = project; }

    void Run();

private:
    inline static Editor *m_instance = nullptr;

    Project    *m_currProject = nullptr;
    EditorState m_state;
    EditorUI    m_ui;
    Window      m_window;

    Editor();
};
