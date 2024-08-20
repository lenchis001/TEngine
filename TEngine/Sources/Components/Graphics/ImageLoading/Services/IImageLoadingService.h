#ifndef TENGINE_IIMAGELOADINGSERVICE_H
#define TENGINE_IIMAGELOADINGSERVICE_H

#include "string"
#include "memory"

#include "Components/Graphics/ImageLoading/Models/Image.h"

namespace TEngine::Components::Graphics::ImageLoading::Services
{
    class IImageLoadingService
    {
    public:
        virtual void initialize() = 0;

        virtual std::shared_ptr<TEngine::Components::Graphics::ImageLoading::Models::Image> load(const std::string &path) = 0;

        virtual ~IImageLoadingService() = default;
    };
}

#endif // TENGINE_IIMAGELOADINGSERVICE_H