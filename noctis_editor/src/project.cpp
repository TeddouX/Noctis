#include "project.hpp"

#include <fmt/format.h>
#include <noctis/logger.hpp>
#include <noctis/scene/scene_manager.hpp>

#include "asset_management/editor_asset_manager.hpp"

namespace NoctisEditor
{

Project::Project(const fs::path &rootDir, const std::string &name)
    : m_rootDir(rootDir), 
    m_name(name), 
    m_assetManager(std::make_shared<EditorAssetManager>())
{
}


bool Project::Load(bool firstTime)
{
    fs::path projFilePath = m_rootDir / fmt::format("{}.nocproj", m_name);

    if (firstTime)
    {
        LOG_INFO("Creating project: {}", m_rootDir.string());
        
        // Create all directories
        fs::create_directories(GetAssetsFolder());
        fs::create_directories(GetScenesFolder());
    
        json j{
            {"name", m_name}
        };

        Noctis::Filesystem::WriteCBOR(projFilePath, json::to_cbor(j));
    }
    else
    {
        LOG_INFO("Loading project: {}", m_rootDir.string());

        // Get name from the first project file that is found
        for (const auto &entry : fs::directory_iterator(m_rootDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".nocproj")
            {
                auto cborData = Noctis::Filesystem::ReadCBOR(entry.path());
                json j = json::from_cbor(cborData);

                m_name = j["name"];
            }
        }

        // Temporary
        fs::create_directories(GetAssetsFolder());
    
        LoadScenes();
    }

    m_assetManager->SetRootFolder(GetAssetsFolder());
    m_assetManager->InitEmbedded();
    Noctis::AssetManagerAccessor::Set(m_assetManager);
    
    SCENE_MANAGER().SetScenesFolder(GetScenesFolder());

    m_loaded = true;
    
    return true;
}


void Project::LoadScenes()
{
    LOG_INFO(
        "Loading scenes from folder {}", 
        GetScenesFolder().string()
    );

    SCENE_MANAGER().SetScenesFolder(GetScenesFolder());

    if (!fs::exists(GetScenesFolder()))
    {
        LOG_WARN(
            "The scene folder ({}) doesn't exist, creating one now...",
            GetScenesFolder().string()
        );
        fs::create_directories(GetScenesFolder());
        return;  
    }

    for (const auto &entry : fs::directory_iterator(GetScenesFolder()))
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


fs::path Project::GetScenesFolder() const
{
    return m_rootDir / "Scenes";
}


fs::path Project::GetAssetsFolder() const
{
    return m_rootDir / "Assets";
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

