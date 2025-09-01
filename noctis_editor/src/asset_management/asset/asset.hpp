#pragma once
#include <memory>
#include <string>

#include <noctis/asset/asset.hpp>
#include <noctis/rendering/texture.hpp>
#include <noctis/rendering/shader.hpp>
#include <noctis/rendering/model.hpp>
#include <noctis/property/property_holder.hpp>

namespace NoctisEditor
{

template <typename T>
struct IEditorAsset : public Noctis::IAsset<T>, public Noctis::IPropertyHolder
{
    fs::path Path;

    std::string GetName() const override { return this->Name; }
};

}
