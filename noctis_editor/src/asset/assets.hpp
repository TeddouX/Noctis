#pragma once
#include <memory>

#include <engine/asset/asset.hpp>
#include <engine/rendering/texture.hpp>
#include <engine/rendering/shader.hpp>
#include <engine/rendering/model.hpp>

namespace NoctisEditor
{

template <typename T>
struct IEditorAsset : public Noctis::IAsset<T>
{
    fs::path Path;
};


struct TextureAsset : public IEditorAsset<Noctis::Texture> 
{
    TextureAsset(
        const std::string &name, 
        std::shared_ptr<Noctis::Texture> texture, 
        const fs::path &path)
    {
        Name = name;
        Asset = texture;
        Path = path;
    };
};

struct ShaderAsset : public IEditorAsset<Noctis::Shader> 
{
    ShaderAsset(
        const std::string &name, 
        std::shared_ptr<Noctis::Shader> shader, 
        const fs::path &path)
    {
        Name = name;
        Asset = shader;
        Path = path;
    };
};

struct ModelAsset : public IEditorAsset<Noctis::Model>
{
    ModelAsset(
        const std::string &name, 
        std::shared_ptr<Noctis::Model> model, 
        const fs::path &path)
    {
        Name = name;
        Asset = model;
        Path = path;
    };
};

}
