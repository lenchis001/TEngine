#ifndef TENGINE_PLUGIN_IPLUGINIMAGE_H
#define TENGINE_PLUGIN_IPLUGINIMAGE_H

#include "PixelTypes.h"

namespace TEngine::Components::Graphics::ImageLoading::Plugin
{
    class IPluginImage
    {
    public:
        virtual ~IPluginImage() = default;

        virtual PixelType getPixelType() const = 0;

        virtual unsigned int getDataSize() const = 0;

        virtual char *getData() const = 0;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
    };
}

#endif // TENGINE_PLUGIN_IPLUGINIMAGE_H