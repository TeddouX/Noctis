#pragma once
#include <noctis/window.hpp>

#include "project.hpp"
#include "ui/editor_ui.hpp"
#include "asset_management/editor_asset_manager.hpp"

#define EDITOR() NoctisEditor::Editor::GetInstance()

namespace NoctisEditor
{

class EditorUI;

enum class EditorState
{
    PROJECT_SELECTION,
    IN_EDITOR
};

class Editor
{
public:
    static Editor &GetInstance();

    EditorState GetState() const { return this->m_state; }
    void SetState(EditorState state) { this->m_state = state; }

    Project *GetCurrProject() { return this->m_currProject.get(); }
    void SetCurrProject(std::unique_ptr<Project> project) { this->m_currProject = std::move(project); }

    void Run();
    
private:
    static Editor s_instance;
    
    std::shared_ptr<Noctis::Window> m_window;
    std::unique_ptr<Project>        m_currProject;
    EditorState m_state;
    EditorUI    m_ui;
    
    Editor();
};

}
