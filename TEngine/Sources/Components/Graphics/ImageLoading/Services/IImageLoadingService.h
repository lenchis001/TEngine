#ifndef TENGINE_IIMAGELOADINGSERVICE_H
#define TENGINE_IIMAGELOADINGSERVICE_H

#include "string"
#include "memory"

#include "Components/Graphics/ImageLoading/Models/Texture.h"

namespace TEngine::Components::Graphics::ImageLoading::Services
{
    class IImageLoadingService
    {
    public:
        virtual std::shared_ptr<TEngine::Components::Graphics::ImageLoading::Models::Texture> load(const std::string &path) = 0;

        virtual ~IImageLoadingService() = default;
    };
}

#endif // TENGINE_IIMAGELOADINGSERVICE_H