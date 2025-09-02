#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "../engine.hpp"
#include "../rendering/model.hpp"
#include "../rendering/shader.hpp"
#include "asset.hpp"

#define ASSET_MANAGER() Noctis::AssetManagerAccessor::Get()

namespace Noctis
{

class NOCTIS_API IAssetManager
{
public:
    virtual ~IAssetManager() = default;
    // virtual void AddAsset(const std::string &name, AssetType type, std::shared_ptr<IAssetBase> asset) = 0;
    virtual std::shared_ptr<IAssetBase> GetAsset(AssetType type, const std::string &name) = 0;
    virtual bool HasAsset(AssetType type, const std::string &name) = 0;

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
    static void Set(std::shared_ptr<IAssetManager> assetManager) { s_assetManager = assetManager; }
    static std::shared_ptr<IAssetManager> Get();

private:
    static inline std::shared_ptr<IAssetManager> s_assetManager = nullptr;
};

}
