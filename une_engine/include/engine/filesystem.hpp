#pragma once
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "logger.hpp"


namespace fs = std::filesystem;


class UNE_API Filesystem
{
public:
    /// @returns The contents of the file as a string
    static std::string GetFileContents(const fs::path &path);

    /// @returns The name of the file at the end of the path
    static std::string GetFileName(const fs::path &path);

    /// @brief Writes cbor data to a file
    static void WriteCBOR(const fs::path &path, std::vector<uint8_t> cborData);
    
    /// @returns The cbor data that is stored in this file, if any
    static std::vector<uint8_t> ReadCBOR(const fs::path &path);

    /// @brief Sets the contents of the file at the end of the path.
    /// If it doesn't exist, it will be created.
    static void WriteFile(const fs::path &path, const std::string &contents);

    /// @returns `true` if the directory has a child directory
    static bool HasChildDirectory(const fs::path &path);

    /// @brief Accepts environment variables like %USERPROFILE% 
    /// @returns The folder that was selected in the dialog 
    static fs::path FolderSelectDialog(const fs::path &folder, const std::string &title = "Select folder...");
 
    /// @returns A wide string representation of a narrow string
    static std::wstring StrToWStr(const std::string &str);
};
