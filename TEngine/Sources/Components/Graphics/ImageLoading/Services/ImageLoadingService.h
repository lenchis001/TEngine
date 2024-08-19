#ifndef IMAGELOADINGSERVICE_H
#define IMAGELOADINGSERVICE_H

#include "IImageLoadingService.h"

using namespace TEngine::Components::Graphics::ImageLoading::Models;

namespace TEngine::Components::Graphics::ImageLoading::Services {
    class ImageLoadingService : public IImageLoadingService
    {
    public:
        ImageLoadingService() = default;
        ~ImageLoadingService() override;

        std::shared_ptr<Texture> load(const std::string &path) override;
    };
}

#endif // IMAGELOADINGSERVICE_H