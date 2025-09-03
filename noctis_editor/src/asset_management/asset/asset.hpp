#pragma once
#include <memory>
#include <string>

#include <noctis/filesystem.hpp>
#include <noctis/asset/asset.hpp>
#include <noctis/rendering/texture.hpp>
#include <noctis/rendering/shader.hpp>
#include <noctis/rendering/model.hpp>

namespace NoctisEditor
{

struct AssetView
{
    AssetView(int id, fs::directory_entry dirEntry, std::shared_ptr<Noctis::IAssetBase> asset)
        : ID(id), DirEntry(dirEntry), Asset(asset) {}
    
    int ID;
    fs::directory_entry DirEntry;
    std::shared_ptr<Noctis::IAssetBase> Asset;
};

template <typename T>
struct IEditorAsset : public Noctis::IAsset<T>
{
    fs::path Path;
};

}
