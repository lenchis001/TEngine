#ifdef __ANDROID__

#ifndef TENGINE_ANDROID_FILE_SERVICE_H
#define TENGINE_ANDROID_FILE_SERVICE_H

#include <android/asset_manager.h>

#include "FileService.h"

namespace TEngine::Components::Core::Filesystem
{
    class AndroidFileService : public FileService
    {
    public:
        AndroidFileService(AAssetManager *assetManager);

        std::string readAsString(const std::string &path) override;

        std::vector<uint8_t> readAsBytes(const std::string &path) override;

        std::string toAbsolutePath(const std::string &path) const override;
    private:
        AAssetManager *_assetManager;
    };
}

#endif // TENGINE_ANDROID_FILE_SERVICE_H

#endif