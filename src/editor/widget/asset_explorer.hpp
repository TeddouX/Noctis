#pragma once
#include <imgui_internal.h>

#include "widget.hpp"
#include "../../core/project.hpp"
#include "../../core/filesystem.hpp"


class AssetExplorerWidget : public IWidget
{
public:
    static constexpr std::string_view name = "Asset Explorer";

    void Render() override;
    
private:
    ImGuiID m_dockspaceID = 0;

    void RenderFolderView() const;
    void DockFolderViewWindow();
    void IterateDirectory(const fs::directory_entry &entry) const;
};
