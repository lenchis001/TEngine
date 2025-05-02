#ifdef __ANDROID__

#include "AndroidFileService.h"

#define GENERATED_PATH "generated/"

using namespace TEngine::Components::Core::Filesystem;

AndroidFileService::AndroidFileService(AAssetManager *assetManager)
    : _assetManager(assetManager)
{
}

std::string AndroidFileService::read(const std::string &path)
{
    std::string finalPath = path;

    // Check if the path starts with "bundle://" - remove this prefix and read from the asset manager
    if (path.find(BUNDLE_PATH) == 0 || path.find(BUILD_IN_BUNDLE_PATH) == 0)
    {
        // Remove the "bundle://" prefix
        finalPath = _removePrefix(finalPath, BUNDLE_PATH);

        // Replace "buildin_bundle://" with "generated/" if exists
        finalPath = _replacePrefix(finalPath, BUILD_IN_BUNDLE_PATH, GENERATED_PATH);

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
        return FileService::read(path);
    }
}

std::string AndroidFileService::_replacePrefix(const std::string &path, const std::string &prefix, const std::string &replacement)
{
    if (path.find(prefix) == 0)
    {
        return replacement + path.substr(prefix.length());
    }
    return path;
}

#endif // __ANDROID__