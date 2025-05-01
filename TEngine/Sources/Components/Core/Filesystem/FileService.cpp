#include "FileService.h"

#include <cstring>
#include <fstream>

using namespace TEngine::Components::Core::Filesystem;

std::string FileService::read(const std::string &path)
{
    std::string finalPath = path;

    // Check if the path starts with "bundle://" - remove this prefix (so it's a desktop platform)
    if (path.find(BUNDLE_PATH) == 0)
    {
        // Remove the "bundle://" prefix
        finalPath = path.substr(strlen(BUNDLE_PATH));
    }

    std::ifstream file(finalPath);
    if (!file.is_open())
    {
        return "";
    }

    // Read the entire file into a string
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return content;
}
