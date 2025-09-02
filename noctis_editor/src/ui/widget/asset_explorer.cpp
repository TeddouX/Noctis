#include "asset_explorer.hpp"

#include <algorithm>
#include <noctis/asset/asset.hpp>

#include "../../asset_management/importer/texture_importer.hpp"
#include "../../asset_management/asset/asset.hpp"
#include "../../utils/imgui_utils.hpp"
#include "../../editor.hpp"

namespace NoctisEditor
{

AssetExplorerWidget::AssetExplorerWidget(std::shared_ptr<PropertiesWidget> propertiesWidget)
    : m_propertiesWidget(propertiesWidget)
{
    m_folderIconTex = LoadTextureFromFile("./assets/images/asset_explorer/folder_icon.png");
    m_fileIconTex = LoadTextureFromFile("./assets/images/asset_explorer/file_icon.png");
}


void AssetExplorerWidget::Render()
{
    ImGui::Begin(GetName().c_str());
    
    Project *proj = EDITOR().GetCurrProject();
    if (!proj)
    {
        ImGui::End();
        return;
    }

    if (m_currFolder.empty())
        m_currFolder = proj->GetAssetsFolder();
    
    RenderMenu();

    m_assetViews = proj->GetAssetManager()->GetAssetViews(m_currFolder);

    RenderAssetBrowser();
    
    ImGui::End();
}


void AssetExplorerWidget::RenderMenu()
{
    const fs::path &assetsFolder = EDITOR().GetCurrProject()->GetAssetsFolder();

    std::vector<fs::path> allFolders;

    fs::path current;
    bool startCollecting = false;
    for (const auto& part : m_currFolder) 
    {
        if (part == assetsFolder.stem())
            startCollecting = true;

        if (current.empty()) 
            current = part;
        else 
            current /= part;
        
        if (startCollecting)
            allFolders.push_back(current);
    }


    for (size_t i = 0; i < allFolders.size(); i++)
    {
        const auto &folder = allFolders[i];

        bool clicked = NoctisEditor::ClickableText(folder.stem().string().c_str());
        if (clicked)
            m_currFolder = folder;

        
        if (i < allFolders.size() - 1)
        {
            ImGui::SameLine();
            ImGui::Text(">");
            ImGui::SameLine();
        }
    }

    if (ImGui::Button("Create..."))
        ImGui::OpenPopup("CREATE##ASSET_EXPLORER");

    static std::optional<Noctis::AssetType> type;
    bool shouldOpenPopup = false;
    if (ImGui::BeginPopup("CREATE##ASSET_EXPLORER"))
    {
        if (ImGui::MenuItem("Folder"))
            shouldOpenPopup = true;

        ImGui::Separator();

        if (ImGui::MenuItem("Script"))
        {
            shouldOpenPopup = true;
            type = Noctis::AssetType::SCRIPT;
        }
        
        if (ImGui::MenuItem("Material"))
        {
            shouldOpenPopup = true;
            type = Noctis::AssetType::MATERIAL;
        }

        if (ImGui::MenuItem("Shader"))
        {
            shouldOpenPopup = true;
            type = Noctis::AssetType::SHADER;
        }

        ImGui::EndPopup();
    }

    if (shouldOpenPopup)
        ImGui::OpenPopup("Name##ASSET_EXPLORER");

    const ImVec2 center = ImGui::GetMainViewport()->GetCenter();
    ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));

    if (ImGui::BeginPopupModal(
        "Name##ASSET_EXPLORER", 
        nullptr, 
        ImGuiWindowFlags_AlwaysAutoResize))
    {
        static std::string name;

        ImGui::Separator();
        NoctisEditor::InlinedLabel("Name: ");
        NoctisEditor::ResizableInputText("##INPUT", name, false);

        if (ImGui::Button("OK", ImVec2(120, 0))) 
        {
            // Not a folder
            if (type.has_value())
            {
                std::string extension;
                switch (type.value())
                {
                case Noctis::AssetType::SCRIPT:   extension = ".as";     break;
                case Noctis::AssetType::MATERIAL: extension = ".nocmat"; break;
                case Noctis::AssetType::SHADER:   extension = ".glsl";   break;
                default: break;
                }

                const std::string fileName = name + extension;
                const fs::path filePath = m_currFolder / fileName;

                Noctis::Filesystem::WriteFile(filePath, "");
            }
            else
            {
                const fs::path folderPath = m_currFolder / name;
                fs::create_directories(folderPath);
            }

            name.clear();
            type.reset();

            ImGui::CloseCurrentPopup();
        }

        ImGui::SetItemDefaultFocus();
        ImGui::SameLine();

        if (ImGui::Button("Cancel", ImVec2(120, 0)))
        {
            name.clear();
            type.reset();

            ImGui::CloseCurrentPopup(); 
        }

        ImGui::EndPopup();
    }

    ImGui::Separator();
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
                    auto assetView = m_assetViews[itemIdx];
                    bool isFolder = assetView.DirEntry.is_directory();

                    ImGui::PushID(assetView.ID);

                    const ImVec2 cursorPos = ImVec2(
                        cursorStartPos.x + (itemIdx % m_columnCount) * m_iconStep, 
                        cursorStartPos.y + lineIdx * m_iconStep
                    );
                    ImGui::SetCursorScreenPos(cursorPos);
                    
                    bool selected = m_assetSelection.Contains((ImGuiID)assetView.ID);
                    bool visible = ImGui::IsRectVisible(iconSize2D);
                    ImGui::Selectable(
                        "", 
                        selected, 
                        isFolder 
                        ? ImGuiSelectableFlags_AllowDoubleClick 
                        : ImGuiSelectableFlags_None, 
                        iconSize2D
                    );

                    if (ImGui::IsItemHovered()
                        && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left) 
                        && isFolder)
                        m_currFolder = assetView.DirEntry.path();

                    if (!visible)
                    {
                        ImGui::PopID();
                        continue;
                    }

                    const ImVec2 imageMin(cursorPos.x, cursorPos.y);
                    const ImVec2 imageMax(cursorPos.x + m_iconSize, cursorPos.y + m_iconSize);

                    ImGui::SetCursorScreenPos(imageMin);
                    ImGui::Image(
                        isFolder ? m_folderIconTex->GetID() : m_fileIconTex->GetID(),
                        ImVec2(imageMax.x - imageMin.x, imageMax.y - imageMin.y)
                    );

                    std::string assetName = assetView.DirEntry.path().stem().string();
                    const float textWidth = ImGui::CalcTextSize(assetName.c_str()).x;
                    const ImVec2 textPos(imageMin.x, imageMax.y - ImGui::GetFontSize());

                    ImGui::RenderTextEllipsis(
                        drawList,
                        textPos,
                        imageMax,
                        imageMax.x,
                        imageMax.x,
                        assetName.c_str(),
                        assetName.c_str() + assetName.size(),
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

}
