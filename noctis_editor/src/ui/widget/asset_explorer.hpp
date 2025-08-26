#pragma once
#include <imgui_internal.h>

#include <engine/filesystem.hpp>

#include "widget.hpp"


class Texture;


struct AssetView
{
    int ID;
    fs::directory_entry DirEntry;

    AssetView(int id, const fs::directory_entry &dirEntry)
        : ID(id), DirEntry(dirEntry) {}
};


class AssetExplorerWidget : public IWidget
{
public:
    AssetExplorerWidget();

    static constexpr std::string_view name = "Asset Explorer";

    void Render() override;
    
private:
    std::unique_ptr<Texture> m_folderIconTex;
    std::unique_ptr<Texture> m_fileIconTex;

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
    
    std::vector<AssetView> m_assetViews;
    ImGuiSelectionBasicStorage m_assetSelection;

    void UpdateLayoutSizes(float availWidth);
    void UpdateAssetViews();
    void RenderAssetBrowser();
};
