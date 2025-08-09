#include "scene/scene_manager.hpp"


SceneManager &SceneManager::GetInstance()
{
    static SceneManager sm;
    return sm;
}


void SceneManager::AddScene(const std::string &name)
{
    if (this->m_scenesFolder.empty())
    {
        LOG_ERR("Scenes folder hasn't been set. Exiting now...");
        exit(1);
    }

    Scene scene(name, this->m_scenesFolder);
    this->m_scenes.emplace(name, scene);
}


void SceneManager::AddSceneFromPath(const fs::path &path)
{
    Scene scene(path);
    this->m_scenes.emplace(scene.GetName(), scene);
}


void SceneManager::RemoveScene(const std::string &name)
{
    this->m_scenes.erase(name);
}


void SceneManager::SaveCurrScene()
{
    if (this->m_currScene.empty())
    {
        LOG_ERR("No scene is selected.");
        return;
    }

    this->GetCurrScene()->Save();
}


void SceneManager::SetCurrScene(const std::string &name)
{
    // If the current scene is set, unload it
    if (this->m_currScene == name)
        return;

    if (!this->m_currScene.empty())
        this->GetCurrScene()->Unload();

    // If the scene exists
    if (this->m_scenes.contains(name))
    {
        this->m_currScene = name;

        Scene *currScene = this->GetCurrScene();

        if (!currScene)
        {
            LOG_ERR("Current scene couldn't be found in the scene manager's registry.");
            return;
        }
        else
            currScene->Load();
    }
    else
        LOG_ERR("Scene {} couldn't be set as current scene because it doesn't exist.", name);
}


Scene *SceneManager::GetCurrScene()
{
    if (this->m_currScene.empty())
        return nullptr;

    auto it = this->m_scenes.find(this->m_currScene);
    if (it == this->m_scenes.end())
    {
        LOG_ERR("Scene {} doesn't exist.", this->m_currScene);
        return nullptr;
    }

    return &it->second;
}
