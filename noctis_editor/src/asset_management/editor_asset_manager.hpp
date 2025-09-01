#pragma once
#include <algorithm>

#include <noctis/asset/asset_manager.hpp>
#include <noctis/filesystem.hpp>

namespace NoctisEditor
{

class EditorAssetManager : public Noctis::IAssetManager
{
public:
    static EditorAssetManager &GetInstance();

    void SetRootFolder(const fs::path &folder) { this->m_root = folder; }

    void InitEmbedded() override;
    
    void AddFile(const fs::path &file);
    
    void AddModel(const fs::path &file);
    void AddShader(const fs::path &file);
    void AddTexture(const fs::path &file);
    
    std::shared_ptr<Noctis::IAssetBase> GetAsset(Noctis::AssetType type, const std::string &name) override;
    
private:
    EditorAssetManager() = default;
    
    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();

    std::unordered_map<Noctis::AssetType, std::vector<std::shared_ptr<Noctis::IAssetBase>>> m_assetCache;
    fs::path m_root;
};

}
