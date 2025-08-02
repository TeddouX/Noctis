#include "project.hpp"



Project::Project(const fs::path &rootDir)
    : m_rootDir(rootDir)
{
}


void Project::Init(const fs::path &rootDir)
{
    LOG_INFO("Initializing project: {}", rootDir.string())

    if (m_instance)
    {
        LOG_ERR("Project instance already initialized.")
        return;
    }

    m_instance = new Project(rootDir);

    // Temporary
    Filesystem::CreateDirs(m_instance->GetAssetsFolder());
    
    // Load all embedded assets
    AssetManager::GetInstance().LoadEmbedded();

    m_instance->LoadScenes();
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


Project *Project::GetInstance()
{
    if (!m_instance)
    {
        LOG_ERR("Project instance not initialized.")
        return nullptr;
    }

    return m_instance;
}


const fs::path Project::GetScenesFolder()
{
    return fmt::format("{}\\Scenes", this->m_rootDir.string());
}


const fs::path Project::GetAssetsFolder()
{
    return fmt::format("{}\\Assets", this->m_rootDir.string());
}
