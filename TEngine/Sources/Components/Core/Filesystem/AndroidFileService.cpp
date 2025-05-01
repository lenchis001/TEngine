#ifdef __ANDROID__

#include "AndroidFileService.h"

using namespace TEngine::Components::Core::Filesystem;

AndroidFileService::AndroidFileService(AAssetManager *assetManager)
    : _assetManager(assetManager)
{
}

std::string AndroidFileService::read(const std::string &path)
{
    AAsset *asset = AAssetManager_open(_assetManager, path.c_str(), AASSET_MODE_BUFFER);
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

#endif // __ANDROID__