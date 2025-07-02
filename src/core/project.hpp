#pragma once
#include <string>
#include <filesystem>
#include <fmt/format.h>

#include "logger.hpp"


#define SCENE_FOLDER() Project::GetInstance()->GetScenesFolder()


namespace fs = std::filesystem;


class Project
{
public:
    static void       Init(const std::string &rootDir);
    static Project   *GetInstance();

    const std::string GetScenesFolder();
    const std::string GetAssetsFolder();

private:
    Project(const std::string &rootDir);

    std::string     m_rootDir;
    static Project *m_instance;
};


