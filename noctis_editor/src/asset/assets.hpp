#pragma once
#include <memory>

#include <engine/asset/asset.hpp>
#include <engine/rendering/texture.hpp>
#include <engine/rendering/shader.hpp>
#include <engine/rendering/model.hpp>


template <typename T>
struct IEditorAsset : public IAsset<T>
{
    fs::path Path;
};


struct TextureAsset : public IEditorAsset<Texture> 
{
    TextureAsset(const std::string &name, std::shared_ptr<Texture> texture, const fs::path &path)
    {
        Name = name;
        Asset = texture;
        Path = path;
    };
};

struct ShaderAsset : public IEditorAsset<Shader> 
{
    ShaderAsset(const std::string &name, std::shared_ptr<Shader> shader, const fs::path &path)
    {
        Name = name;
        Asset = shader;
        Path = path;
    };
};

struct ModelAsset : public IEditorAsset<Model>
{
    ModelAsset(const std::string &name, std::shared_ptr<Model> model, const fs::path &path)
    {
        Name = name;
        Asset = model;
        Path = path;
    };
};
