#include "filesystem.hpp"

// Stop windows from polluting the 
// other files' global namespace
#include <windows.h>
#include <shobjidl.h>
#include <shlobj.h>


std::string Filesystem::GetFileContents(const fs::path &path)
{
    if (!fs::exists(path))
    {
        LOG_ERR("File {} doesn't exist.", path.string());
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
        LOG_ERR("Failed to open file {} for writing.", filePath.string());
        return;
    }

    file.write(
        reinterpret_cast<const char*>(cborData.data()),
        cborData.size()
    );
}


std::vector<uint8_t> Filesystem::ReadCBOR(const fs::path &filePath)
{
    std::ifstream file(filePath, std::ios::binary | std::ios::ate);

    if (!file) 
    {
        LOG_ERR("Failed to open file {} for reading.", filePath.string());
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
        LOG_ERR("Failed to read file contents ({}).", filePath.string());
        return {};
    }

    return buffer;
}


void Filesystem::WriteFile(const fs::path &path, const std::string &contents)
{
    std::ofstream file(path);

    if (file.bad())
    {
        LOG_ERR("Failed to open file {} for writing.", path.string());
        return;
    }

    file << contents;

    file.close();
}


bool Filesystem::HasChildDirectory(const fs::path &path)
{
    for (const auto& entry : fs::directory_iterator(path))
        if (entry.is_directory())
            return true;

    return false;
}


fs::path Filesystem::FolderSelectDialog(const fs::path &folder, const std::string &title)
{
    HRESULT res = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);

    if (!SUCCEEDED(res)) 
        return fs::path(); 
    
    // Create the file dialog instance
    IFileDialog* fileDialog = NULL;
    res = CoCreateInstance(
        CLSID_FileOpenDialog, 
        NULL, 
        CLSCTX_INPROC_SERVER,               
        IID_PPV_ARGS(&fileDialog)
    );

    if (!SUCCEEDED(res))
    {
        CoUninitialize();
        return fs::path(); 
    }

    // Expand folder path
    wchar_t expandedFolderPath[MAX_PATH];
    ExpandEnvironmentStringsW(
        StrToWStr(folder.string()).c_str(), 
        expandedFolderPath, 
        MAX_PATH
    );

    // Set the file dialog's title
    fileDialog->SetTitle(StrToWStr(title).c_str());

    IShellItem* userProfileFolder = NULL;
    res = SHCreateItemFromParsingName(expandedFolderPath, NULL, IID_PPV_ARGS(&userProfileFolder));


    if (SUCCEEDED(res)) 
    {
        // Set the file dialog starting folder
        fileDialog->SetFolder(userProfileFolder);
        userProfileFolder->Release();
    }

    
    // Set file select dialog options
    DWORD fileDialogOptions;
    fileDialog->GetOptions(&fileDialogOptions);
    fileDialog->SetOptions(fileDialogOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);

    // Show file dialog
    res = fileDialog->Show(NULL);

    if (!SUCCEEDED(res))
    {
        fileDialog->Release();
        CoUninitialize();

        return fs::path();
    }

    // Get the result from the file dialog
    IShellItem* item;
    res = fileDialog->GetResult(&item);
    // Release the file dialog because 
    // it is not needed anymore
    fileDialog->Release();

    if (!SUCCEEDED(res)) 
    {
        CoUninitialize();
        return fs::path(); 
    }

    PWSTR filePath;
    // Get file path of selected item
    res = item->GetDisplayName(SIGDN_FILESYSPATH, &filePath);

    if (SUCCEEDED(res)) 
    {
        // Free memory
        CoTaskMemFree(filePath);
        item->Release();

        return fs::path(filePath);
    }

    item->Release();

    return fs::path();
}


std::wstring Filesystem::StrToWStr(const std::string &str)
{
    int size = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
    std::wstring wideStr(size, 0);
    MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wideStr[0], size);

    return wideStr;
}
