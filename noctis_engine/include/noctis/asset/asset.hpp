#pragma once
#include <string>
#include <memory>

#include "../engine.hpp"

#define CUBE_MODEL_NAME "Cube"
#define CYLINDER_MODEL_NAME "Cylinder"
#define MONKEY_MODEL_NAME "Monkey"
#define SPHERE_MODEL_NAME "Sphere"

#define DEFAULT_SHADER_NAME "Default"
#define LIT_SHADER_NAME "Lit"

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
