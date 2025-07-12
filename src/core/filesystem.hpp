#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "logger.hpp"


namespace fs = std::filesystem;


class Filesystem
{
public:
    /// @returns The contents of the file as a string
    static std::string GetFileContents(const fs::path &path);

    /// @brief Sets the contents of the file at the end of the path.
    /// If it doesn't exist, it will be created.
    static void SetFileContents(const fs::path &path, const std::string &contents);

    /// @brief If non existant, create all directories from the path
    static void CreateDirs(const fs::path &path);
};
