#pragma once
#include <noctis/rendering/material.hpp>
#include <noctis/property/color_property.hpp>

#include "asset.hpp"

namespace NoctisEditor
{

struct MaterialAsset : public IEditorAsset<Noctis::Material> 
{
    MaterialAsset(
        const std::string &name, 
        std::shared_ptr<Noctis::Material> material, 
        const fs::path &path)
    {
        Name = name;
        Asset = material;
        Path = path;
    };

    std::vector<std::shared_ptr<Noctis::IPropertyBase>> GetProperties() override
    {
        return {
            std::make_shared<Noctis::ColorProperty>(GETTER_FOR_REF(this->Asset->GetColor()), "Color"),
            std::make_shared<Noctis::ColorProperty>(GETTER_FOR_REF(this->Asset->GetSpecular()), "Specular Color")
        };  
    }
};

}
