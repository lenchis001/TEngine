#ifndef PNG_IMAGE_LOADING_PLUGIN_H
#define PNG_IMAGE_LOADING_PLUGIN_H

#include "memory"
#include "IImageLoadingPlugin.h"
#include <png.h>

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace PngLoadingPlugin
{
    class PngLoadingPluginImplementation : public IImageLoadingPlugin
    {
    public:
        PngLoadingPluginImplementation();
        virtual ~PngLoadingPluginImplementation() override;

        virtual std::vector<std::string> getSupportedExtensions() const override;

        virtual std::shared_ptr<IPluginImage> load(const std::vector<uint8_t>& data) override;
    };
}

extern "C"
{
    std::shared_ptr<IImageLoadingPlugin> load();
}

#endif // PNG_IMAGE_LOADING_PLUGIN_H