#pragma once
#include <unordered_map>

#include "scene.hpp"
#include "../logger.hpp"


#define SCENE_MANAGER() SceneManager::GetInstance()


class SceneManager
{
public:
    static SceneManager &GetInstance();

    inline void SetScenesFolder(const fs::path &path) { this->m_scenesFolder = path; }

    void   AddScene(const std::string &name);
    void   AddSceneFromPath(const fs::path &path);
    void   RemoveScene(const std::string &name);

    /// @brief Saves the current scene, if set
    void   SaveCurrScene();
    void   SetCurrScene(const std::string &name);
    Scene *GetCurrScene();

private:
    std::unordered_map<std::string, Scene> m_scenes;
    fs::path    m_scenesFolder;
    std::string m_currScene;
};