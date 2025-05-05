#ifdef __ANDROID__

#include <boost/filesystem.hpp>

#include "AndroidFileService.h"

using namespace TEngine::Components::Core::Filesystem;

AndroidFileService::AndroidFileService(AAssetManager *assetManager)
    : _assetManager(assetManager)
{
}

std::string AndroidFileService::readAsString(const std::string &path)
{
    std::string finalPath = path;

    // Check if the path starts with "bundle://" - remove this prefix and read from the asset manager
    if (path.find(BUNDLE_PATH) == 0)
    {
        // Remove the "bundle://" prefix
        finalPath = _removePrefix(finalPath, BUNDLE_PATH);

        AAsset *asset = AAssetManager_open(_assetManager, finalPath.c_str(), AASSET_MODE_BUFFER);
        if (!asset)
        {
            return "";
        }

        off_t length = AAsset_getLength(asset);
        std::string content(length, '\0');
        AAsset_read(asset, &content[0], length);

        AAsset_close(asset);

        return content;
    }
    else
    {
        // For other cases, use the base class implementation
        return FileService::readAsString(path);
    }
}

std::vector<uint8_t> AndroidFileService::readAsBytes(const std::string &path)
{
    std::string finalPath = path;

    // Check if the path starts with "bundle://" - remove this prefix and read from the asset manager
    if (path.find(BUNDLE_PATH) == 0)
    {
        // Remove the "bundle://" prefix
        finalPath = _removePrefix(finalPath, BUNDLE_PATH);

        AAsset *asset = AAssetManager_open(_assetManager, finalPath.c_str(), AASSET_MODE_BUFFER);
        if (!asset)
        {
            return {};
        }

        off_t length = AAsset_getLength(asset);
        std::vector<uint8_t> content(length);
        AAsset_read(asset, content.data(), length);

        AAsset_close(asset);

        return content;
    }
    else
    {
        // For other cases, use the base class implementation
        return FileService::readAsBytes(path);
    }
}

std::string AndroidFileService::toAbsolutePath(const std::string &path) const
{
    if (path.find(BUNDLE_PATH) == 0)
    {
        return path;
    }

    auto currentPath = boost::filesystem::current_path() / path;

    return currentPath.string();
}

#endif // __ANDROID__