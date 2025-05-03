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

        std::string read(const std::string &path) override;

    private:
        AAssetManager *_assetManager;
    };
}

#endif // TENGINE_ANDROID_FILE_SERVICE_H

#endif