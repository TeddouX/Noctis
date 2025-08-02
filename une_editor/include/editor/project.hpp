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
    Project(const fs::path &rootDir);

    const fs::path GetScenesFolder();
    const fs::path GetAssetsFolder();

private:
    fs::path m_rootDir;

    void LoadScenes();
};
