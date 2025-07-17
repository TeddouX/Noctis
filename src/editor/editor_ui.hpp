#pragma once
#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>

#include "imgui_utils.hpp"
#include "widget/scene_display.hpp"
#include "widget/scene_tree.hpp"
#include "widget/asset_explorer.hpp"
#include "widget/actor_properties.hpp"
#include "widget/console.hpp"
#include "../core/window.hpp"
#include "../core/scene/scene_manager.hpp"


struct EditorUIState
{
    bool showCreateScenePopup = false;
};


class EditorUI
{
public:
    EditorUI(Window &window, const std::string &glslVers);

    void Render();

private:
    EditorUIState m_state;
    Window &m_mainWindow;
    float   m_imGuiScale;

    std::vector<std::unique_ptr<IWidget>> m_allWidgets;

    void DockDisplays() const;
    void ShowCreateSceneModal();
    void ShowLoadSceneMenu();
    void ShowMenuBar();
    void HandleInput();
    void HandleState();
};
