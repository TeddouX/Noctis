#pragma once
#include <string>

#include "../engine.hpp"

namespace Noctis
{

enum class AssetType
{
    MODEL,
    MATERIAL,
    TEXTURE,
    SHADER,
    SCRIPT
};


struct NOCTIS_API IAssetBase
{
    virtual ~IAssetBase() = default;

    std::string Name;
};


template <typename T>
struct NOCTIS_API IAsset : public IAssetBase
{
    std::shared_ptr<T> Asset;
};

}

namespace std 
{
    template <>
    struct hash<Noctis::AssetType> 
    {
        std::size_t operator()(const Noctis::AssetType& at) const noexcept 
        {
            return std::hash<int>()(static_cast<int>(at));
        }
    };
}
