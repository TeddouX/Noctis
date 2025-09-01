#pragma once
#include <memory>
#include <noctis/rendering/shader.hpp>

#include "asset.hpp"

namespace NoctisEditor
{

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

    std::vector<std::shared_ptr<Noctis::IPropertyBase>> GetProperties() override
    {
        return {

        };
    }
};

}