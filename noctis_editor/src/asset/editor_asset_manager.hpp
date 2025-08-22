#pragma once
#include <algorithm>

#include <engine/asset/asset_manager.hpp>
#include <engine/filesystem.hpp>

#include "assets.hpp"


class EditorAssetManager : public IAssetManager
{
public:
    static EditorAssetManager &GetInstance();

    void SetRootFolder(const fs::path &folder) { this->m_root = folder; }

    void InitEmbedded() override;
    
    void AddFile(const fs::path &file);
    
    void AddModel(const fs::path &file);
    void AddShader(const fs::path &file);
    void AddTexture(const fs::path &file);
    
    std::shared_ptr<IAssetBase> GetAsset(AssetType type, const std::string &name) override;
    
private:
    EditorAssetManager() = default;
    
    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();

    std::unordered_map<AssetType, std::vector<std::shared_ptr<IAssetBase>>> m_assetCache;
    fs::path m_root;
};
