#include "editor_asset_manager.hpp"

#include "importer/model_importer.hpp"
#include "importer/texture_importer.hpp"

namespace NoctisEditor
{

bool IsImageFile(const fs::path &path);
bool IsModelFile(const fs::path &path);
bool IsShaderFile(const fs::path &path);


EditorAssetManager &EditorAssetManager::GetInstance()
{
    static EditorAssetManager eam;
    return eam;
}


void EditorAssetManager::InitEmbedded()
{
    InitializeEmbeddedModels();
    InitializeEmbeddedShaders();
}


void EditorAssetManager::AddFile(const fs::path &file)
{
    if (IsImageFile(file))
        AddTexture(file);
    else if (IsModelFile(file))
        AddModel(file);
    else if (IsShaderFile(file))
        AddShader(file);
}


void EditorAssetManager::AddModel(const fs::path &file)
{
    auto ma = std::make_shared<ModelAsset>(
        file.stem().string(),
        LoadModel(file),
        file
    );

    this->m_assetCache[Noctis::AssetType::MODEL].push_back(ma);
}


void EditorAssetManager::AddShader(const fs::path &file)
{
    std::string fileContents = Noctis::Filesystem::GetFileContents(file);
    if (fileContents.empty())
        return;

    auto sa = std::make_shared<ShaderAsset>(
        file.stem().string(),
        std::make_shared<Noctis::Shader>(fileContents.c_str()),
        file
    );
    
    this->m_assetCache[Noctis::AssetType::SHADER].push_back(sa);
}


void EditorAssetManager::AddTexture(const fs::path &file)
{
    auto ta = std::make_shared<TextureAsset>(
        file.stem().string(),
        LoadTextureFromFile(file),
        file
    );

    this->m_assetCache[Noctis::AssetType::TEXTURE].push_back(ta);
}


std::shared_ptr<Noctis::IAssetBase> 
EditorAssetManager::GetAsset(Noctis::AssetType type, const std::string &name)
{
    std::vector<std::shared_ptr<Noctis::IAssetBase>> &vec = this->m_assetCache.at(type);

    for (auto &asset : vec)
    {
        if (asset->Name == name)
            return asset;
    }

    return nullptr;
}


void EditorAssetManager::InitializeEmbeddedModels()
{
    AddModel(".\\assets\\models\\Cube.obj");
    AddModel(".\\assets\\models\\Cylinder.obj");
    AddModel(".\\assets\\models\\Monkey.obj");
    AddModel(".\\assets\\models\\Sphere.obj");
}


void EditorAssetManager::InitializeEmbeddedShaders()
{
    AddShader(".\\assets\\shaders\\Default.glsl");
    AddShader(".\\assets\\shaders\\Lit.glsl");
}


bool IsImageFile(const fs::path &path)
{
    if (fs::is_regular_file(path))
        return false;

    std::string extension = path.extension().string();

    return extension == ".png" 
        || extension == ".jpeg"; 
    //  || extension == ".hdr";
}


bool IsModelFile(const fs::path &path)
{
    if (fs::is_regular_file(path))
        return false;

    return path.extension() == ".obj"; 
}


bool IsShaderFile(const fs::path &path)
{
    if (fs::is_regular_file(path))
        return false;

    return path.extension() == ".glsl"; 
}

}
