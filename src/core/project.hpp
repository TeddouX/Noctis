#pragma once
#include <string>
#include <filesystem>
#include <fmt/format.h>

#include "logger.hpp"
#include "filesystem.hpp"
#include "scene/scene_manager.hpp"


#define PROJECT() Project::GetInstance()


class Project
{
public:
    static void       Init(const fs::path &rootDir);
    static Project   *GetInstance();

    const fs::path       GetScenesFolder();
    const fs::path       GetAssetsFolder();

private:
    Project(const fs::path &rootDir);

    static Project *m_instance;
    fs::path        m_rootDir;

    void LoadScenes();
};
