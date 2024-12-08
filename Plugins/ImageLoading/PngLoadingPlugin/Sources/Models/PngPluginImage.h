#ifndef PNG_PLUGIN_IMAGE_H
#define PNG_PLUGIN_IMAGE_H

#include "IPluginImage.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace PngLoadingPlugin::Models
{
    class PngPluginImage : public IPluginImage
    {
    public:
        PngPluginImage(int width, int height, char *data, unsigned int dataSize);
        ~PngPluginImage() override;

        virtual PixelType getPixelType() const override;

        virtual unsigned int getDataSize() const override;

        virtual char *getData() const override;

        virtual int getWidth() const override;
        virtual int getHeight() const override;

    private:
        int _width;
        int _height;
        char *_data;
        unsigned int _dataSize;
    };
}

#endif // PNG_PLUGIN_IMAGE_H