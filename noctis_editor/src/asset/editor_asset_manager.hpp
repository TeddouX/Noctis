#include <algorithm>

#include <engine/asset/asset_manager.hpp>
#include <engine/filesystem.hpp>

#include "assets.hpp"


class EditorAssetManager : public IAssetManager
{
public:
    EditorAssetManager() = default;

    void InitEmbedded() override;

    void AddFile(const fs::path &file);

    std::shared_ptr<IAssetBase> GetAsset(AssetType type, const std::string &name) override;

private:
    void InitializeEmbeddedModels();
    void InitializeEmbeddedShaders();

    std::unordered_map<AssetType, std::vector<std::shared_ptr<IAssetBase>>> m_assetCache;
};
