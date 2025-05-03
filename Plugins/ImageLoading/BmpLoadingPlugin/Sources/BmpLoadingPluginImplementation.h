#ifndef BMP_IMAGE_LOADING_PLUGIN_H
#define BMP_IMAGE_LOADING_PLUGIN_H

#include "IImageLoadingPlugin.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace BmpLoadingPlugin
{
    class BmpLoadingPluginImplementation : public IImageLoadingPlugin
    {
    public:
        BmpLoadingPluginImplementation();
        virtual ~BmpLoadingPluginImplementation() override;

        virtual std::vector<std::string> getSupportedExtensions() const override;

        virtual std::shared_ptr<IPluginImage> load(const std::vector<uint8_t>& data) override;
    };
}

extern "C"
{
    std::shared_ptr<IImageLoadingPlugin> load();
}

#endif // BMP_IMAGE_LOADING_PLUGIN_H