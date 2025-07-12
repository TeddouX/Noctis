#include "filesystem.hpp"


std::string Filesystem::GetFileContents(const fs::path &path)
{
    if (!fs::exists(path))
    {
        LOG_ERR("File {} doesn't exist.", path.string())
        return "";
    }

    std::ifstream fileStream;
    fileStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try
    {
        fileStream.open(path);

        std::stringstream buf;
        buf << fileStream.rdbuf();

        return buf.str();
    }
    catch(const std::ios_base::failure& e)
    {
        LOG_ERR("Error while opening file: {}", e.what());
        return "";
    }
}


void Filesystem::SetFileContents(const fs::path &path, const std::string &contents)
{
    std::ofstream file(path);

    file << contents;

    file.close();
}


void Filesystem::CreateDirs(const fs::path &path)
{
    if (!fs::exists(path))
        fs::create_directories(path);
}
