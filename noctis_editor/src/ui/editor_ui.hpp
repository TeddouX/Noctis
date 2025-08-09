#pragma once
#include <string>
#include <imgui.h>

#include <engine/window.hpp>

#include "project_selection.hpp"
#include "widget/widget.hpp"


struct EditorUIState
{
    bool showCreateScenePopup = false;
};


class EditorUI
{
public:
    EditorUI(Window &window, const char *glslVers);

    void Render();

private:
    ProjectSelectionUI m_psUI;
    EditorUIState m_state;
    Window &m_mainWindow;
    float m_imGuiScale;

    ImFont *m_font;

    std::vector<std::shared_ptr<IWidget>> m_allWidgets;

    void DockDisplays() const;
    void ShowCreateSceneModal();
    void ShowMenuBar();
    void HandleInput();
    void HandleState();
};
