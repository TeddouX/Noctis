#include "project.hpp"


Project::Project(const fs::path &rootDir)
    : m_rootDir(rootDir)
{
    LOG_INFO("Initializing project: {}", rootDir.string())

    // Temporary
    Filesystem::CreateDirs(this->GetAssetsFolder());
    
    // Load all embedded assets
    AssetManager::GetInstance().LoadEmbedded();

    this->LoadScenes();
} 


void Project::LoadScenes()
{
    LOG_INFO(
        "Loading scenes from folder {}", 
        this->GetScenesFolder().string()
    )

    SCENE_MANAGER().SetScenesFolder(this->GetScenesFolder());

    if (!fs::exists(this->GetScenesFolder()))
    {
        LOG_WARN(
            "The scene folder ({}) doesn't exist, creating one now...",
            this->GetScenesFolder().string()
        )
        Filesystem::CreateDirs(this->GetScenesFolder());
        return;  
    }

    for (const auto &entry : fs::directory_iterator(this->GetScenesFolder()))
    {
        fs::path path = entry.path();
        // Is the entry is a json file ?
        if (path.extension() == ".scene")
        {
            LOG_INFO("Found scene: {}", path.string())
            
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
