#pragma once
#include <algorithm>

#include <noctis/asset/asset_manager.hpp>
#include <noctis/filesystem.hpp>

#include "asset/asset.hpp"

namespace NoctisEditor
{

class EditorAssetManager : public Noctis::IAssetManager
{
public:
    EditorAssetManager() = default;
    
    void SetRootFolder(const fs::path &folder) { this->m_root = folder; }
    
    void InitEmbedded();

    std::vector<AssetView> GetAssetViews(const fs::path& folderPath);

    std::shared_ptr<Noctis::IAssetBase> AddFile(const fs::path &file);
    
    std::shared_ptr<Noctis::IAssetBase> GetAsset(Noctis::AssetType type, const std::string &name) override;
    std::shared_ptr<Noctis::IAssetBase> GetAsset(const fs::path &path);

    bool HasAsset(Noctis::AssetType type, const std::string &name) override;
    bool HasAsset(const fs::path &path);
    
private:
    fs::path m_root;

    std::unordered_map<
        fs::path, 
        std::shared_ptr<Noctis::IAssetBase>> m_assetFileCache;

    std::unordered_map<
        Noctis::AssetType, 
        std::vector<std::shared_ptr<Noctis::IAssetBase>>> m_assetCache;
};

}
