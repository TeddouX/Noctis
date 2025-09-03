#pragma once
#include <string>
#include <memory>

#include "project_selection.hpp"

namespace Noctis
{
    class Window;
}

namespace NoctisEditor
{

class IWidget;

class EditorUI
{
public:
    EditorUI(std::shared_ptr<Noctis::Window> window, const char *glslVers);

    void Render();

private:
    std::shared_ptr<Noctis::Window> m_mainWindow;
    ProjectSelectionUI m_psUI;
    float m_imGuiScale;

    std::vector<std::shared_ptr<IWidget>> m_allWidgets;

    void DockDisplays() const;
    void ShowCreateSceneModal();
    void ShowMenuBar();
    void HandleInput();
    void HandleState();
};

}
