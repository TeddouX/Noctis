#pragma once
#include <unordered_map>

#include "scene.hpp"
#include "../logger.hpp"


#define SCENE_MANAGER() SceneManager::GetInstance()


class SceneManager
{
public:
    static SceneManager &GetInstance();

    void   AddScene(const Scene &scene);
    void   RemoveScene(const std::string &name);

    void   SetCurrScene(const std::string &name);
    Scene  *GetCurrScene();

private:
    std::unordered_map<std::string, Scene> m_scenes;
    std::string m_currScene;
};