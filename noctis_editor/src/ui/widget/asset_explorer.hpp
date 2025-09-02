#pragma once
#include <optional>
#include <imgui_internal.h>
#include <noctis/filesystem.hpp>

#include "../../asset_management/asset/asset.hpp"
#include "widget.hpp"

namespace Noctis
{
    class Texture;
}

namespace NoctisEditor
{

class PropertiesWidget;
struct AssetView;

class AssetExplorerWidget : public IWidget
{
public:
    AssetExplorerWidget(std::shared_ptr<PropertiesWidget> propertiesWidget);

    static std::string GetName() { return "Asset Explorer"; }

    void Render() override;
    
private:
    std::unique_ptr<Noctis::Texture> m_folderIconTex;
    std::unique_ptr<Noctis::Texture> m_fileIconTex;

    ImGuiID m_dockspaceID = 0;
    fs::path m_currFolder;

    float m_iconSize = 64.f;
    float m_iconSpacing = 10.f;
    float m_selectedIconSpacing = 4.f;
    
    // Layout
    float m_outerPadding = 10.f;
    int m_columnCount = 0;
    int m_lineCount = 0;
    // Used for rendering the icons
    // m_iconSpacing - m_selectedIconSpacing
    float m_selectableSpacing = 0.f;
    // m_iconSize + m_iconSpacing
    float m_iconStep = 0.f;
    float m_layoutIconSpacing = 0.f;
    
    std::shared_ptr<PropertiesWidget> m_propertiesWidget;
    std::vector<AssetView> m_assetViews;
    ImGuiSelectionBasicStorage m_assetSelection;

    void RenderMenu();
    void UpdateLayoutSizes(float availWidth);
    void RenderAssetBrowser();
};

}
