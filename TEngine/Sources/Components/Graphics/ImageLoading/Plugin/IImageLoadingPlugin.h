#ifndef TENGINE_PLUGIN_IIMAGELOADINGPLUGIN_H
#define TENGINE_PLUGIN_IIMAGELOADINGPLUGIN_H

#include "memory"
#include "string"
#include "vector"

#include "IPluginImage.h"

namespace TEngine::Components::Graphics::ImageLoading::Plugin {
    class IImageLoadingPlugin
    {
    public:
        virtual ~IImageLoadingPlugin() = default;

        virtual std::vector<std::string> getSupportedExtensions() const = 0;

        virtual std::shared_ptr<IPluginImage> load(const std::vector<uint8_t>& data) = 0;
    };
}

#endif // TENGINE_PLUGIN_IIMAGELOADINGPLUGIN_H