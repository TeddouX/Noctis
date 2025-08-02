#pragma once
#include <imgui_internal.h>

#include <engine/filesystem.hpp>

#include "widget.hpp"

class Editor;

class AssetExplorerWidget : public IWidget
{
public:
    AssetExplorerWidget() = default;

    static constexpr std::string_view name = "Asset Explorer";

    void Render() override;
    
private:
    ImGuiID m_dockspaceID = 0;

    void RenderFolderView() const;
    void DockFolderViewWindow();
    void IterateDirectory(const fs::directory_entry &entry) const;
};
