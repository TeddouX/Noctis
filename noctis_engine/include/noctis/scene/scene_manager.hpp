#pragma once
#include <unordered_map>

#include "scene.hpp"
#include "../logger.hpp"

#define SCENE_MANAGER() Noctis::SceneManager::GetInstance()

namespace Noctis
{

class NOCTIS_API SceneManager
{
public:
    static SceneManager &GetInstance();

    inline void SetScenesFolder(const fs::path &path) { this->m_scenesFolder = path; }

    inline const std::unordered_map<std::string, Scene> &GetAllScenes() const { return this->m_scenes; }

    void AddScene(const std::string &name);
    void AddSceneFromPath(const fs::path &path);
    void RemoveScene(const std::string &name);

    /// @brief Saves the current scene, if set
    void SaveCurrScene();
    /// @brief Sets the current scene
    void   SetCurrScene(const std::string &name);
    Scene *GetCurrScene();

private:
    std::unordered_map<std::string, Scene> m_scenes;
    fs::path    m_scenesFolder;
    std::string m_currScene;
};

}
