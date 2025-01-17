#ifndef PNG_PLUGIN_IMAGE_H
#define PNG_PLUGIN_IMAGE_H

#include "IPluginImage.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace PngLoadingPlugin::Models
{
    class PngPluginImage : public IPluginImage
    {
    public:
        PngPluginImage(int width, int height, const std::vector<char>& data);
        ~PngPluginImage() override;

        virtual PixelType getPixelType() const override;

        virtual const std::vector<char>& getData() const override;

        virtual int getWidth() const override;
        virtual int getHeight() const override;

    private:
        int _width;
        int _height;
        std::vector<char> _data;
    };
}

#endif // PNG_PLUGIN_IMAGE_H