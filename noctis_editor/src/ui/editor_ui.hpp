#pragma once
#include <string>
#include <imgui.h>

#include <engine/window.hpp>

#include "project_selection.hpp"
#include "widget/widget.hpp"

namespace NoctisEditor
{

struct EditorUIState
{
    bool showCreateScenePopup = false;
};


class EditorUI
{
public:
    EditorUI(std::shared_ptr<Noctis::Window> window, const char *glslVers);

    void Render();

private:
    std::shared_ptr<Noctis::Window> m_mainWindow;
    ProjectSelectionUI m_psUI;
    EditorUIState m_state;
    float m_imGuiScale;

    ImFont *m_font;

    std::vector<std::shared_ptr<IWidget>> m_allWidgets;

    void DockDisplays() const;
    void ShowCreateSceneModal();
    void ShowMenuBar();
    void HandleInput();
    void HandleState();
};

}
