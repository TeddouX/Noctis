#include "editor_asset_manager.hpp"

#include "importer/model_importer.hpp"
#include "importer/texture_importer.hpp"
#include "asset/material_asset.hpp"
#include "asset/model_asset.hpp"
#include "asset/script_asset.hpp"
#include "asset/shader_asset.hpp"
#include "asset/texture_asset.hpp"

namespace NoctisEditor
{

bool IsImageFile(const fs::path &path);
bool IsModelFile(const fs::path &path);

std::vector<AssetView> 
EditorAssetManager::GetAssetViews(const fs::path& folderPath)
{
    std::vector<AssetView> assetViews;

    int id = 0;
    for (const auto &entry : fs::directory_iterator(folderPath))
    {
        // Try getting an asset
        std::shared_ptr<Noctis::IAssetBase> asset = 
            AddFile(entry.path());

        AssetView av(id, entry, asset);
        assetViews.push_back(av);

        id++;
    }

    return assetViews;
}

void EditorAssetManager::InitEmbedded()
{
    AddFile(".\\assets\\models\\Cube.obj");
    AddFile(".\\assets\\models\\Cylinder.obj");
    AddFile(".\\assets\\models\\Monkey.obj");
    AddFile(".\\assets\\models\\Sphere.obj");

    AddFile(".\\assets\\shaders\\Default.glsl");
    AddFile(".\\assets\\shaders\\Lit.glsl");
}

std::shared_ptr<Noctis::IAssetBase> 
EditorAssetManager::AddFile(const fs::path &file)
{
    if (HasAsset(file))
        return GetAsset(file);

    if (!file.has_extension())
        return nullptr;

    std::shared_ptr<Noctis::IAssetBase> asset;
    if (IsImageFile(file))
    {
        asset = std::make_shared<TextureAsset>(
            file.stem().string(),
            LoadTextureFromFile(file),
            file
        );

        m_assetCache[Noctis::AssetType::TEXTURE].push_back(asset);
    }
    else if (IsModelFile(file))
    {
        asset = std::make_shared<ModelAsset>(
            file.stem().string(),
            LoadModel(file),
            file
        );

        m_assetCache[Noctis::AssetType::MODEL].push_back(asset);
    }
    else if (file.extension() == ".glsl")
    {
        std::string fileContents = Noctis::Filesystem::GetFileContents(file);
        if (fileContents.empty())
            return nullptr;

        asset = std::make_shared<ShaderAsset>(
            file.stem().string(),
            std::make_shared<Noctis::Shader>(fileContents.c_str()),
            file
        );
        
        m_assetCache[Noctis::AssetType::SHADER].push_back(asset);
    }
    else if (file.extension() == ".nocmat")
    {
        std::vector<uint8_t> cborData = Noctis::Filesystem::ReadBytes(file); 
        json j = json::from_cbor(cborData);

        
    }

    if (asset)
    {
        m_assetFileCache.emplace(file, asset);
        return asset;
    }

    return nullptr;
}

std::shared_ptr<Noctis::IAssetBase> 
EditorAssetManager::GetAsset(Noctis::AssetType type, const std::string &name)
{
    for (auto &asset : m_assetCache.at(type))
    {
        if (asset->Name == name)
            return asset;
    }

    return nullptr;
}

std::shared_ptr<Noctis::IAssetBase> EditorAssetManager::GetAsset(const fs::path &path)
{
    if (HasAsset(path))
        return m_assetFileCache.at(path);
    else
        return nullptr;
}


bool EditorAssetManager::HasAsset(Noctis::AssetType type, const std::string &name)
{
    for (auto &asset : m_assetCache.at(type))
        if (asset->Name == name)
            return true;
    return false;
}

bool EditorAssetManager::HasAsset(const fs::path &path)
{
    return m_assetFileCache.contains(path);
}


bool IsImageFile(const fs::path &path)
{
    std::string extension = path.extension().string();

    return extension == ".png" 
        || extension == ".jpeg"; 
    //  || extension == ".hdr";
}

bool IsModelFile(const fs::path &path)
{
    return path.extension().string() == ".obj";
}

}
