#ifndef TENGINE_IMAGE_H
#define TENGINE_IMAGE_H

#include <vector>

#include "PixelType.h"

namespace TEngine::Components::Graphics::ImageLoading::Models
{
    class Image
    {
    public:
        Image(PixelType pixelType, const std::vector<char>& data, int width, int height);
        ~Image();

        PixelType getPixelType() const;

        const std::vector<char>& getData() const;

        int getWidth() const;
        int getHeight() const;

    private:
        PixelType _pixelType;
        std::vector<char> _data;
        int _width;
        int _height;
    };
};

#endif // TENGINE_IMAGE_H