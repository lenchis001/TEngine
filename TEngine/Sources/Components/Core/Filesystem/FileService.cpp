#include "FileService.h"

#include <cstring>
#include <fstream>

#include <boost/filesystem.hpp>

using namespace TEngine::Components::Core::Filesystem;

std::string FileService::readAsString(const std::string &path)
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

std::vector<uint8_t> FileService::readAsBytes(const std::string &path)
{
    std::string finalPath = path;

    // Check if the path starts with "bundle://" - remove this prefix (so it's a desktop platform)
    finalPath = _removePrefix(finalPath, BUNDLE_PATH);
    finalPath = _removePrefix(finalPath, BUILD_IN_BUNDLE_PATH);

    std::ifstream file(finalPath, std::ios::binary | std::ios::ate);
    if (!file.is_open())
    {
        return {};
    }

    std::streamsize size = file.tellg();
    file.seekg(0, std::ios::beg);

    std::vector<uint8_t> buffer(size);
    if (!file.read(reinterpret_cast<char *>(buffer.data()), size))
    {
        return {};
    }

    file.close();

    return buffer;
}

std::string FileService::_removePrefix(const std::string &path, const std::string &prefix)
{
    if (path.find(prefix) == 0)
    {
        return path.substr(prefix.length());
    }
    return path;
}

std::string FileService::toAbsolutePath(const std::string &path) const
{
    auto currentPath = boost::filesystem::current_path() / path;

    return currentPath.string();
}