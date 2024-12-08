#ifndef BMP_PLUGIN_IMAGE_H
#define BMP_PLUGIN_IMAGE_H

#include "IPluginImage.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace BmpLoadingPlugin::Models
{
    class BmpPluginImage : public IPluginImage
    {
    public:
        BmpPluginImage(int width, int height, char *data, unsigned int dataSize);
        ~BmpPluginImage() override;

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

#endif // BMP_PLUGIN_IMAGE_H