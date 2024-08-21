#ifndef BMP_IMAGE_LOADING_PLUGIN_H
#define BMP_IMAGE_LOADING_PLUGIN_H

#include "memory"

#include "IImageLoadingPlugin.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace BmpImageLoadingPlugin
{
    class BmpImageLoadingPluginImplementation : public IImageLoadingPlugin
    {
    public:
        BmpImageLoadingPluginImplementation();
        virtual ~BmpImageLoadingPluginImplementation() override;

        virtual std::vector<std::string> getSupportedExtensions() const override;

        virtual std::shared_ptr<IPluginImage> load(const std::string &path) override;
    };
}

extern "C"
{
    std::shared_ptr<IImageLoadingPlugin> load();
}

#endif // BMP_IMAGE_LOADING_PLUGIN_H