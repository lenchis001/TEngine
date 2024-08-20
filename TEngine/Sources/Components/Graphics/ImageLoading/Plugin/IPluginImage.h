#ifndef TENGINE_PLUGIN_IPLUGINIMAGE_H
#define TENGINE_PLUGIN_IPLUGINIMAGE_H

namespace TEngine::Components::Graphics::ImageLoading::Plugin
{
    class IPluginImage
    {
    public:
        ~IPluginImage() = default;

        virtual void *getData() const;

        virtual int getWidth() const;
        virtual int getHeight() const;
    };
}

#endif // TENGINE_PLUGIN_IPLUGINIMAGE_H