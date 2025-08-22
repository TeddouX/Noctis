#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>

#include "asset.hpp"
#include "../engine.hpp"
#include "../rendering/shader.hpp"
#include "../rendering/model.hpp"


#define CUBE_MODEL_NAME "Cube"
#define CYLINDER_MODEL_NAME "Cylinder"
#define MONKEY_MODEL_NAME "Monkey"
#define SPHERE_MODEL_NAME "Sphere"

#define DEFAULT_SHADER_NAME "Default"
#define LIT_SHADER_NAME "Lit"

#define ASSET_MANAGER() AssetManagerAccessor::Get()


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
