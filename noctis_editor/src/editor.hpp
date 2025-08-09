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
    static Editor &GetInstance();

    EditorState GetState() const { return this->m_state; }
    void SetState(EditorState state) { this->m_state = state; }

    Project &GetCurrProject() { return this->m_currProject; }
    void SetCurrProject(const Project &project) { this->m_currProject = project; };
    
    void Run();
    
private:
    static Editor s_instance;
    
    Project     m_currProject;
    EditorState m_state;
    Window      m_window;
    EditorUI    m_ui;
    
    Editor();
};
