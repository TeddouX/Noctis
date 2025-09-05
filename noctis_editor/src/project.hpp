#pragma once
#include <string>
#include <noctis/filesystem.hpp>
#include <noctis/ecs/entity.hpp>

#include "scene_manager.hpp"

namespace NoctisEditor
{

class EditorAssetManager;

class Project
{
public:
    Project(const fs::path &rootDir, const std::string &name);

    bool Load(bool firstTime);

    std::shared_ptr<EditorAssetManager> GetAssetManager() { return m_assetManager; }
    SceneManager &GetSceneManager() { return m_sm; }
    const fs::path &GetRootDir() const { return m_rootDir; }
    fs::path GetScenesFolder() const;
    fs::path GetAssetsFolder() const;

    void SetSelectedEntity(const Noctis::Entity &entity) { m_selectedEntity = entity; }
    Noctis::Entity GetSelectedEntity() const { return m_selectedEntity; }

    static bool IsValidProjectFolder(const fs::path &path);

private:
    fs::path     m_rootDir;
    std::string  m_name;

    std::shared_ptr<EditorAssetManager> m_assetManager;
    SceneManager m_sm;

    Noctis::Entity m_selectedEntity;
    
    void LoadScenes();
};

}
