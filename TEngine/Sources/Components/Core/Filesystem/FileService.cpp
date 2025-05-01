#include "FileService.h"

#include <cstring>
#include <fstream>

using namespace TEngine::Components::Core::Filesystem;

std::string FileService::read(const std::string &path)
{
    std::string finalPath = path;

    // Check if the path starts with "bundle://" - remove this prefix (so it's a desktop platform)
    finalPath = _removePrefix(finalPath, BUNDLE_PATH);
    finalPath = _removePrefix(finalPath, BUILD_IN_BUNDLE_PATH);

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

std::string FileService::_removePrefix(const std::string &path, const std::string &prefix)
{
    if (path.find(prefix) == 0)
    {
        return path.substr(prefix.length());
    }
    return path;
}