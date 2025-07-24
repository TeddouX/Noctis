#include "asset_explorer.hpp"


void AssetExplorerWidget::Render()
{
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin(std::string(AssetExplorerWidget::name).c_str());

    this->DockFolderViewWindow();
    this->RenderFolderView();
    
    ImGui::End();
    ImGui::PopStyleVar();
}


void AssetExplorerWidget::DockFolderViewWindow()
{
    // Create a dockspace for this widget
    this->m_dockspaceID = ImGui::GetID("AssetExplorerDockspace");
    ImGui::DockSpace(this->m_dockspaceID, ImVec2(0, 0), ImGuiDockNodeFlags_PassthruCentralNode);

    // Initialize only once
    static bool dockInitialized = false;
    if (!dockInitialized)
    {
        dockInitialized = true;

        // Clear any previous layout
        ImGui::DockBuilderRemoveNode(this->m_dockspaceID);
        ImGui::DockBuilderAddNode(this->m_dockspaceID, ImGuiDockNodeFlags_DockSpace);
        ImGui::DockBuilderSetNodeSize(this->m_dockspaceID, ImGui::GetMainViewport()->Size);
        
        ImGuiID mainDock = this->m_dockspaceID;
        // 20% left, 80% right
        ImGuiID DockLeft = ImGui::DockBuilderSplitNode(mainDock, ImGuiDir_Left, 0.20f, nullptr, &mainDock);

        // Dock folder view window
        ImGui::DockBuilderDockWindow("Folder View", DockLeft);

        ImGui::DockBuilderFinish(this->m_dockspaceID);
    }
}



void AssetExplorerWidget::RenderFolderView() const
{
    ImGui::Begin("Folder View", nullptr, ImGuiWindowFlags_NoMove);

    // Iterate through all directories in the assets folder
    for (const auto &entry : fs::directory_iterator(PROJECT()->GetAssetsFolder()))
        this->IterateDirectory(entry);

    ImGui::End();
}


void AssetExplorerWidget::IterateDirectory(const fs::directory_entry &entry) const
{
    if (!entry.is_directory())
        return; 

    ImGui::PushID(entry.path().string().c_str());
    
    bool open = ImGui::TreeNodeEx(
        entry.path().filename().string().c_str(),
        // If the directory has other directories in it
        // render it as a leaf node
        (Filesystem::HasChildDirectory(entry) ? 0 : ImGuiTreeNodeFlags_Leaf)
    );

    if (open)
    {
        for (const auto &childEntry : fs::directory_iterator(entry))
            this->IterateDirectory(childEntry);

        ImGui::TreePop();
    }

    ImGui::PopID();
}
