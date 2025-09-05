#pragma once
#include <memory>
#include <noctis/rendering/model.hpp>

#include "asset.hpp"

namespace NoctisEditor
{

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

    std::vector<std::shared_ptr<Noctis::IPropertyBase>> GetProperties() override
    {
        return {
            
        };
    }
};

}