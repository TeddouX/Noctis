#include "project.hpp"

#include <fmt/format.h>

#include <engine/logger.hpp>
#include <engine/scene/scene_manager.hpp>

#include "asset/editor_asset_manager.hpp"

namespace NoctisEditor
{

Project::Project(const fs::path &rootDir, const std::string &name)
    : m_rootDir(rootDir), m_name(name)
{
}


bool Project::Load(bool firstTime)
{
    fs::path projFilePath = this->m_rootDir / fmt::format("{}.nocproj", this->m_name);

    if (firstTime)
    {
        LOG_INFO("Creating project: {}", this->m_rootDir.string());
        
        // Create all directories
        fs::create_directories(this->GetAssetsFolder());
        fs::create_directories(this->GetScenesFolder());
    
        json j{
            {"name", this->m_name}
        };

        Noctis::Filesystem::WriteCBOR(projFilePath, json::to_cbor(j));
    }
    else
    {
        LOG_INFO("Loading project: {}", this->m_rootDir.string());

        // Get name from the first project file that is found
        for (const auto &entry : fs::directory_iterator(this->m_rootDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".nocproj")
            {
                auto cborData = Noctis::Filesystem::ReadCBOR(entry.path());
                json j = json::from_cbor(cborData);

                this->m_name = j["name"];
            }
        }

        // Temporary
        fs::create_directories(this->GetAssetsFolder());
    
        this->LoadScenes();
    }

    Noctis::AssetManagerAccessor::Set(&EditorAssetManager::GetInstance());

    EditorAssetManager::GetInstance().InitEmbedded();
    EditorAssetManager::GetInstance().SetRootFolder(this->GetAssetsFolder());
    
    SCENE_MANAGER().SetScenesFolder(this->GetScenesFolder());

    this->m_loaded = true;
    
    return true;
}


void Project::LoadScenes()
{
    LOG_INFO(
        "Loading scenes from folder {}", 
        this->GetScenesFolder().string()
    );

    SCENE_MANAGER().SetScenesFolder(this->GetScenesFolder());

    if (!fs::exists(this->GetScenesFolder()))
    {
        LOG_WARN(
            "The scene folder ({}) doesn't exist, creating one now...",
            this->GetScenesFolder().string()
        );
        fs::create_directories(this->GetScenesFolder());
        return;  
    }

    for (const auto &entry : fs::directory_iterator(this->GetScenesFolder()))
    {
        fs::path path = entry.path();
        // Is the entry is a json file ?
        if (path.extension() == ".scene")
        {
            LOG_INFO("Found scene: {}", path.string());
            
            // Create a scene with the file's name
            // The scene class handles loading when necessary
            SCENE_MANAGER().AddSceneFromPath(path);
        }
    }
}


fs::path Project::GetScenesFolder()
{
    return this->m_rootDir / "Scenes";
}


fs::path Project::GetAssetsFolder()
{
    return this->m_rootDir / "Assets";
}


bool Project::IsValidProjectFolder(const fs::path &path)
{
    if (!fs::is_directory(path))
        return false;

    // check if there is a ".proj" file in the directory
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".nocproj")
            return true;
    }

    return false;
}

}

