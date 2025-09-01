#pragma once
#include <memory>
#include <string>

#include <engine/asset/asset.hpp>
#include <engine/rendering/texture.hpp>
#include <engine/rendering/shader.hpp>
#include <engine/rendering/model.hpp>
#include <engine/property/property_holder.hpp>

namespace NoctisEditor
{

template <typename T>
struct IEditorAsset : public Noctis::IAsset<T>, public Noctis::IPropertyHolder
{
    fs::path Path;
};

}
