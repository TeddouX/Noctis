#pragma once
#include <string>
#include <filesystem>
#include <fmt/format.h>

#include <engine/logger.hpp>
#include <engine/filesystem.hpp>
#include <engine/scene/scene_manager.hpp>


class Project
{
public:
    Project()
        : m_loaded(false) {}

    Project(const fs::path &rootDir, const std::string &name);
    Project(const fs::path &rootDir);

    bool Load(bool firstTime);

    const fs::path GetScenesFolder();
    const fs::path GetAssetsFolder();

    bool IsLoaded() { return this->m_loaded; }

    static bool IsValidProjectFolder(const fs::path &path);

private:
    std::string m_name;
    fs::path    m_rootDir;
    bool        m_loaded;

    void LoadScenes();
};
