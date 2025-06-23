#pragma once
#include <string>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include "widgets/scene_display.hpp"
#include "widgets/scene_tree.hpp"
#include "widgets/asset_explorer.hpp"
#include "widgets/actor_properties.hpp"
#include "../core/window.hpp"


class EditorUI
{
public:
    EditorUI(Window &window, const std::string &glslVers);

    void Render();
    void DockDisplays() const;

private:
    float m_imGuiScale;

    // ONLY FOR TESTING
    SceneDisplayWidget w;
    SceneTreeWidget w2;
    AssetExplorerWidget w3;
    ActorPropertiesWidget w4;
};
