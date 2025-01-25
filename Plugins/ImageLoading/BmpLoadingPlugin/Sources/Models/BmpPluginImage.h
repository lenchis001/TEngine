#ifndef BMP_PLUGIN_IMAGE_H
#define BMP_PLUGIN_IMAGE_H

#include "IPluginImage.h"

using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace BmpLoadingPlugin::Models
{
    class BmpPluginImage : public IPluginImage
    {
    public:
        BmpPluginImage(int width, int height, const std::vector<char>& data);
        ~BmpPluginImage() override;

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

#endif // BMP_PLUGIN_IMAGE_H