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


std::string Filesystem::GetFileName(const fs::path &path)
{
    return std::filesystem::path(path).stem().string();
}


void Filesystem::WriteCBOR(const fs::path &filePath, std::vector<uint8_t> cborData)
{
    std::ofstream file(filePath, std::ios::binary);

    if (!file)
    {
        LOG_ERR("Failed to open file {} for writing.", filePath.string())
        return;
    }

    file.write(reinterpret_cast<const char*>(cborData.data()), cborData.size());
}    


std::vector<uint8_t> Filesystem::ReadCBOR(const fs::path &filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file) 
    {
        LOG_ERR("Failed to open file {} for reading.", filePath.string())
        return {};
    }

    // Get the current position of the read cursor.
    // Because the file was opened using "std::ios::ate"
    // the cursor is at the end.
    std::streamsize fileSize = file.tellg();
    // Move back the read cursor to the begining
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(fileSize);
    // Read the file contents and put them in the buffer
    if (!file.read(reinterpret_cast<char*>(buffer.data()), fileSize)) 
    {
        LOG_ERR("Failed to read file contents ({}).", filePath.string())
        return {};
    }

    return buffer;
}


void Filesystem::WriteFile(const fs::path &path, const std::string &contents)
{
    std::ofstream file(path);

    if (!file)
    {
        LOG_ERR("Failed to open file {} for writing.", path.string())
        return;
    }

    file << contents;

    file.close();
}


void Filesystem::CreateDirs(const fs::path &path)
{
    if (!fs::exists(path))
        fs::create_directories(path);
}

bool Filesystem::HasChildDirectory(const fs::path &path)
{
    for (const auto& entry : fs::directory_iterator(path))
        if (entry.is_directory())
            return true;

    return false;
}
