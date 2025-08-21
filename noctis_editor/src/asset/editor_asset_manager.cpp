#include "editor_asset_manager.hpp"


static bool IsImageFile(const fs::path &path)
{
    if (fs::is_regular_file(path))
        return false;

    std::string extension = path.extension().string();

    return extension == ".png" 
        || extension == ".jpeg"; 
    //  || extension == ".hdr";
}


static bool IsModelFile(const fs::path &path)
{
    if (fs::is_regular_file(path))
        return false;

    return path.extension() == ".obj"; 
}


static bool IsShaderFile(const fs::path &path)
{
    if (fs::is_regular_file(path))
        return false;

    return path.extension() == ".glsl"; 
}


void EditorAssetManager::InitEmbedded()
{
    InitializeEmbeddedModels();
    InitializeEmbeddedShaders();
}


void EditorAssetManager::AddFile(const fs::path &file)
{
    std::string fileName = file.stem().string();

    if (IsImageFile(file))
    {
        auto ta = std::make_shared<TextureAsset>(
            fileName,
            std::make_shared<BasicTexture>(file, TextureType::INVALID),
            file
        );

        this->m_assetCache[AssetType::TEXTURE].push_back(ta);
    }
    else if (IsModelFile(file))
    {
        auto ma = std::make_shared<ModelAsset>(
            fileName,
            Model(file),
            file
        );

        this->m_assetCache[AssetType::MODEL].push_back(ma);
    }
    else if (IsShaderFile(file))
    {
        auto sa = std::make_shared<ShaderAsset>(
            fileName,
            Shader(file),
            file
        );
        
        this->m_assetCache[AssetType::SHADER].push_back(sa);
    }
}


std::shared_ptr<IAssetBase> EditorAssetManager::GetAsset(AssetType type, const std::string &name)
{
    std::vector<std::shared_ptr<IAssetBase>> &vec = this->m_assetCache.at(type);

    for (auto &asset : vec)
    {
        if (asset->Name == name)
            return asset;
    }

    return nullptr;
}


void EditorAssetManager::InitializeEmbeddedModels()
{
    
}


void EditorAssetManager::InitializeEmbeddedShaders()
{

}
