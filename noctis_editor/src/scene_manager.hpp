#pragma once
#include <unordered_map>

#include <noctis/scene.hpp>
#include <noctis/filesystem.hpp>

namespace NoctisEditor
{

class SceneManager
{
public:
    SceneManager(const fs::path &scenesFolder)
        : m_scenesFolder(scenesFolder) {}

    void AddScene(const fs::path &scenePath);
    void CreateScene(const std::string &name);
    void RemoveScene(const std::string &name);

    void SaveCurrentScene();

    const std::unordered_map<std::string, Noctis::Scene> &GetAllScenes() const { return m_scenes; }

    // Also unloads current scene
    void SetCurrentScene(const std::string &name);
    Noctis::Scene *GetCurrentScene() { return m_currScene; }

    void AddEditorSystems(Noctis::Scene &scene);
    void AddRuntimeSystems(Noctis::Scene &scene);

private:
    std::unordered_map<std::string, Noctis::Scene> m_scenes;
    Noctis::Scene *m_currScene = nullptr;
    fs::path       m_currScenePath;
    fs::path       m_scenesFolder;

    fs::path GetScenePath(const std::string &name) const;
};

} // namespace NoctisEditor
