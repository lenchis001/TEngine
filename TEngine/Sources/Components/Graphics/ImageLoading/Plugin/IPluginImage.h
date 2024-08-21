#ifndef TENGINE_PLUGIN_IPLUGINIMAGE_H
#define TENGINE_PLUGIN_IPLUGINIMAGE_H

namespace TEngine::Components::Graphics::ImageLoading::Plugin
{
    class IPluginImage
    {
    public:
        virtual ~IPluginImage() = default;

        virtual void *getData() const = 0;

        virtual int getWidth() const = 0;
        virtual int getHeight() const = 0;
    };
}

#endif // TENGINE_PLUGIN_IPLUGINIMAGE_H