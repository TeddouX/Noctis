#pragma once
#include <string>

#include <engine/filesystem.hpp>

namespace NoctisEditor
{

class Project
{
public:
    Project()
        : m_loaded(false) {}

    Project(const fs::path &rootDir, const std::string &name);

    bool Load(bool firstTime);

    const fs::path &GetRootDir() const { return this->m_rootDir; }
    fs::path GetScenesFolder();
    fs::path GetAssetsFolder();

    bool IsLoaded() { return this->m_loaded; }

    static bool IsValidProjectFolder(const fs::path &path);

private:
    std::string m_name;
    fs::path    m_rootDir;
    bool        m_loaded;

    void LoadScenes();
};

}
