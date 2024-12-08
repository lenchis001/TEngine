#ifndef TENGINE_IMAGE_H
#define TENGINE_IMAGE_H

#include "PixelType.h"

namespace TEngine::Components::Graphics::ImageLoading::Models
{
    class Image
    {
    public:
        Image(PixelType pixelType, char *data, unsigned int dataSize, int width, int height);
        ~Image();

        PixelType getPixelType() const;

        unsigned int getDataSize() const;

        char *getData() const;

        int getWidth() const;
        int getHeight() const;

    private:
        PixelType _pixelType;
        char *_data;
        int _width;
        int _height;
        unsigned int _dataSize;
    };
};

#endif // TENGINE_IMAGE_H