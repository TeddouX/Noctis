#include "asset_explorer.hpp"

#include <algorithm>

#include "../../editor.hpp"
#include "../../asset/importer/texture_importer.hpp"


AssetExplorerWidget::AssetExplorerWidget()
{
    m_folderIconTex = LoadTextureFromFile("./assets/images/asset_explorer/folder_icon.png");
    m_fileIconTex = LoadTextureFromFile("./assets/images/asset_explorer/file_icon.png");
}


void AssetExplorerWidget::Render()
{
    ImGui::Begin(std::string(AssetExplorerWidget::name).c_str());
    
    if (m_currFolder.empty())
        m_currFolder = EDITOR().GetCurrProject().GetAssetsFolder();

    UpdateAssetViews();
    RenderAssetBrowser();
    
    ImGui::End();
}


void AssetExplorerWidget::UpdateLayoutSizes(float availWidth)
{
    m_columnCount = std::max(
        (int)(availWidth / (m_iconSize + m_iconSpacing)),
        1
    );

    if (m_columnCount > 1)
        m_layoutIconSpacing = floorf(availWidth - m_iconSize * m_columnCount) / m_columnCount;

    m_lineCount = ((int)m_assetViews.size() + m_columnCount) / m_columnCount;
    m_selectableSpacing = m_iconSpacing - m_selectedIconSpacing;
    m_iconStep = m_iconSize + m_iconSpacing;
    // m_outerPadding = m_iconSize / 2;
}


void AssetExplorerWidget::UpdateAssetViews()
{
    m_assetViews.clear();

    int id = 0;
    for (const auto &entry : fs::directory_iterator(m_currFolder))
    {
        AssetView v(
            id, 
            entry.path().stem().string(), 
            entry.is_directory() ? m_folderIconTex->GetID() : m_fileIconTex->GetID(), 
            entry.is_directory()
        );

        m_assetViews.push_back(v);
        
        id++;
    }

    std::sort(
        m_assetViews.begin(), m_assetViews.end(),
        [](const AssetView &left, const AssetView &right)
        {
            if (left.IsFolder != right.IsFolder)
                return left.IsFolder;
            return left.Name > right.Name;
        }
    );
}


void AssetExplorerWidget::RenderAssetBrowser()
{
    // Heavily inspired by ImGui's example asset browser:
    // https://github.com/ocornut/imgui/blob/master/imgui_demo.cpp#L10549

    const ImVec2 iconSize2D(m_iconSize, m_iconSize);

    ImGui::SetNextWindowContentSize(ImVec2(
        0.f, 
        m_outerPadding + m_lineCount * (m_iconSize + m_layoutIconSpacing)
    ));

    if (ImGui::BeginChild("Assets"))
    {
        ImDrawList *drawList = ImGui::GetWindowDrawList();

        UpdateLayoutSizes(ImGui::GetContentRegionAvail().x);

        ImVec2 cursorStartPos = ImGui::GetCursorScreenPos();
        cursorStartPos = ImVec2(
            cursorStartPos.x + m_outerPadding, 
            cursorStartPos.y + m_outerPadding
        );
        ImGui::SetCursorScreenPos(cursorStartPos);

        ImGuiMultiSelectFlags msFlags = ImGuiMultiSelectFlags_ClearOnEscape 
            | ImGuiMultiSelectFlags_ClearOnClickVoid
            | ImGuiMultiSelectFlags_BoxSelect2d;
        ImGuiMultiSelectIO* msIO = ImGui::BeginMultiSelect(
            msFlags, 
            m_assetSelection.Size, 
            (int)m_assetViews.size()
        );

        m_assetSelection.UserData = this;
        m_assetSelection.AdapterIndexToStorageId = [](
            ImGuiSelectionBasicStorage *sbs, 
            int idx) -> ImGuiID
        {
            AssetExplorerWidget *ab = (AssetExplorerWidget*)sbs->UserData; 
            return ab->m_assetViews[idx].ID;
        };

        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, 
            ImVec2(m_selectableSpacing, m_selectableSpacing)
        );

        ImGuiListClipper clipper;
        clipper.Begin((int)m_assetViews.size(), m_iconSize);

        // RangeSrc item must never be clipped
        if (msIO->RangeSrcItem != -1)
            clipper.IncludeItemByIndex((int)msIO->RangeSrcItem / m_columnCount);
        
        while (clipper.Step())
        {
            for (int lineIdx = clipper.DisplayStart; lineIdx < clipper.DisplayEnd; lineIdx++)
            {
                const int minItemIdxForLine = lineIdx * m_columnCount;
                const int maxItemIdxForLine = std::min(
                    (lineIdx + 1) * m_columnCount, 
                    (int)m_assetViews.size()
                );

                for (int itemIdx = minItemIdxForLine; itemIdx < maxItemIdxForLine; itemIdx++)
                {
                    AssetView asset = m_assetViews[itemIdx];

                    ImGui::PushID(asset.ID);

                    ImVec2 cursorPos = ImVec2(
                        cursorStartPos.x + (itemIdx % m_columnCount) * m_iconStep, 
                        cursorStartPos.y + lineIdx * m_iconStep
                    );
                    ImGui::SetCursorScreenPos(cursorPos);
                    
                    ImGui::SetNextItemSelectionUserData(itemIdx);
                    bool selected = m_assetSelection.Contains((ImGuiID)asset.ID);
                    bool visible = ImGui::IsRectVisible(iconSize2D);
                    ImGui::Selectable("", selected, ImGuiSelectableFlags_None, iconSize2D);

                    if (ImGui::IsItemToggledSelection())
                        selected = !selected;

                    if (!visible)
                    {
                        ImGui::PopID();
                        continue;
                    }

                    ImVec2 imageMin(cursorPos.x, cursorPos.y);
                    ImVec2 imageMax(cursorPos.x + m_iconSize, cursorPos.y + m_iconSize);
                    // drawList->AddRectFilled(imageMin, imageMax, IM_COL32(255, 0, 0, 255));
                    
                    ImGui::SetCursorScreenPos(imageMin);
                    ImGui::Image(
                        asset.TextureID, 
                        ImVec2(imageMax.x - imageMin.x, imageMax.y - imageMin.y)
                    );

                    const char *assetName = asset.Name.c_str();
                    const float textWidth = ImGui::CalcTextSize(assetName).x;
                    ImVec2 textPos(imageMin.x, imageMax.y - ImGui::GetFontSize());

                    ImGui::RenderTextEllipsis(
                        drawList,
                        textPos,
                        imageMax,
                        imageMax.x,
                        imageMax.x,
                        assetName,
                        assetName + strlen(assetName),
                        nullptr
                    );
                    
                    ImGui::PopID();
                }
            }
        }

        ImGui::PopStyleVar(); // ImGuiStyleVar_ItemSpacing
        
        msIO = ImGui::EndMultiSelect();
        m_assetSelection.ApplyRequests(msIO);
    }

    ImGui::EndChild();
}
