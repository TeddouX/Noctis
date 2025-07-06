#include "scene_manager.hpp"


SceneManager &SceneManager::GetInstance()
{
    static SceneManager sm;
    return sm;
}


void SceneManager::AddScene(Scene *scene)
{
    this->m_scenes.emplace(scene->GetName(), scene);
}


void SceneManager::RemoveScene(const std::string &name)
{
    this->m_scenes.erase(name);
}


void SceneManager::SetCurrScene(const std::string &name)
{
    // If the current scene is set, unload it
    if (!this->m_currScene.empty())
        this->GetCurrScene()->Unload();

    // If the scene exists
    if (this->m_scenes.count(name) > 0)
    {
        this->m_currScene = name;
        this->GetCurrScene()->Load();
    }
    else
        LOG_ERR("Scene {} doesn't exist.", name)
}


Scene *SceneManager::GetCurrScene()
{
    if (this->m_currScene.empty())
    {
        LOG_ERR("The current scene hasn't been set.")
        
        return nullptr;
    }

    return this->m_scenes.at(this->m_currScene);
}
