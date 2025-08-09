#include "project.hpp"

#include <fmt/format.h>

#include <engine/logger.hpp>
#include <engine/scene/scene_manager.hpp>


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

        Filesystem::WriteCBOR(projFilePath, json::to_cbor(j));
    }
    else
    {
        LOG_INFO("Loading project: {}", this->m_rootDir.string());

        // Get name from the first project file that is found
        for (const auto &entry : fs::directory_iterator(this->m_rootDir))
        {
            if (entry.is_regular_file() && entry.path().extension() == ".nocproj")
            {
                auto cborData = Filesystem::ReadCBOR(entry.path());
                json j = json::from_cbor(cborData);

                this->m_name = j["name"];
            }
        }

        // Temporary
        fs::create_directories(this->GetAssetsFolder());
    
        // Load all embedded assets

        this->LoadScenes();
    }

    AssetManager::GetInstance().LoadEmbedded();
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


const fs::path Project::GetScenesFolder()
{
    return fmt::format("{}\\Scenes", this->m_rootDir.string());
}


const fs::path Project::GetAssetsFolder()
{
    return fmt::format("{}\\Assets", this->m_rootDir.string());
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

