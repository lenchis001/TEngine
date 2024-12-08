#ifndef IMAGELOADINGSERVICE_H
#define IMAGELOADINGSERVICE_H

#include "string"
#include "vector"
#include "unordered_map"

#include "Components/Graphics/ImageLoading/Plugin/IImageLoadingPlugin.h"


#include "IImageLoadingService.h"
#include "Mixins/PluginsLoadingAware.hpp"

using namespace TEngine::Mixins;

using namespace TEngine::Components::Graphics::ImageLoading::Models;
using namespace TEngine::Components::Graphics::ImageLoading::Plugin;
using namespace TEngine::Components::Graphics::ImageLoading::Models;

using EnginePixelType = TEngine::Components::Graphics::ImageLoading::Models::PixelType;
using PluginPixelType = TEngine::Components::Graphics::ImageLoading::Plugin::PixelType;

namespace TEngine::Components::Graphics::ImageLoading::Services
{
    class ImageLoadingService : public PluginsLoadingAware<IImageLoadingPlugin>, public IImageLoadingService
    {
    public:
        ImageLoadingService() = default;
        ~ImageLoadingService() override;

        void initialize() override;

        std::shared_ptr<Image> load(const std::string &path) override;
    private:
        static EnginePixelType _toEnginePixelType(PluginPixelType pluginPixelType);
    };
}

#endif // IMAGELOADINGSERVICE_H