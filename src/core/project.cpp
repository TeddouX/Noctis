#include "project.hpp"


Project *Project::m_instance = nullptr;


Project::Project(const std::string &rootDir)
    : m_rootDir(rootDir)
{   
}


void Project::Init(const std::string &rootDir)
{
    if (m_instance)
    {
        LOG_ERR("Project instance already initialized.");
        return;
    }

    m_instance = new Project(rootDir);

    if (!fs::exists(SCENE_FOLDER())) 
        fs::create_directories(SCENE_FOLDER());
} 


Project *Project::GetInstance()
{
    if (!m_instance)
    {
        LOG_ERR("Project instance not initialized.");
        return nullptr;
    }

    return m_instance;
}


const std::string Project::GetScenesFolder()
{
    return fmt::format("{}\\Scenes", this->m_rootDir);
}


const std::string Project::GetAssetsFolder()
{
    return fmt::format("{}\\Assets", this->m_rootDir);
}
