#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "asset.hpp"
#include "../engine.hpp"
#include "../rendering/shader.hpp"
#include "../rendering/model.hpp"

#define ASSET_MANAGER() Noctis::AssetManagerAccessor::Get()

namespace Noctis
{

class NOCTIS_API IAssetManager
{
public:
    virtual ~IAssetManager() = default;
    virtual void InitEmbedded() = 0;
    // virtual void AddAsset(const std::string &name, AssetType type, std::shared_ptr<IAssetBase> asset) = 0;
    virtual std::shared_ptr<IAssetBase> GetAsset(AssetType type, const std::string &name) = 0;

    template <typename T>
    std::shared_ptr<IAsset<T>> GetTyped(AssetType type, const std::string &name)
    {
        return std::dynamic_pointer_cast<IAsset<T>>(
            this->GetAsset(type, name)
        );
    }
};


class NOCTIS_API AssetManagerAccessor
{
public:
    static void Set(IAssetManager *assetManager) { s_assetManager = assetManager; }
    static IAssetManager *Get();

private:
    static inline IAssetManager *s_assetManager = nullptr;
};

}
