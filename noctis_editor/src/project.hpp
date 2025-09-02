#pragma once
#include <string>
#include <noctis/filesystem.hpp>

#include "asset_management/editor_asset_manager.hpp"

namespace NoctisEditor
{

class Project
{
public:
    Project(const fs::path &rootDir, const std::string &name);

    bool Load(bool firstTime);

    std::shared_ptr<EditorAssetManager> GetAssetManager() { return this->m_assetManager; }
    const fs::path &GetRootDir() const { return this->m_rootDir; }
    fs::path GetScenesFolder() const;
    fs::path GetAssetsFolder() const;

    bool IsLoaded() const { return this->m_loaded; }

    static bool IsValidProjectFolder(const fs::path &path);

private:
    std::shared_ptr<EditorAssetManager> m_assetManager;
    std::string m_name;
    fs::path    m_rootDir;
    bool        m_loaded = false;

    void LoadScenes();
};

}
