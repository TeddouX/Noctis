#pragma once
#include <string>
#include <filesystem>
#include <fmt/format.h>

#include "logger.hpp"
#include "asset_manager.hpp"


#define PROJECT() Project::GetInstance()


namespace fs = std::filesystem;


class Project
{
public:
    static void       Init(const std::string &rootDir);
    static Project   *GetInstance();

    const std::string   GetScenesFolder();
    const std::string   GetAssetsFolder();
    inline AssetManager &GetAssetManager() { return this->m_assetManager; };

private:
    Project(const std::string &rootDir);

    static Project *m_instance;
    std::string     m_rootDir;
    AssetManager    m_assetManager;
};


