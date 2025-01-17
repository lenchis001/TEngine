#include "Image.h"

#include <cstring>

using namespace TEngine::Components::Graphics::ImageLoading::Models;

Image::Image(PixelType pixelType, const std::vector<char>& data, int width, int height)
    : _pixelType(pixelType),
      _width(width),
      _height(height),
        _data(data)
{
}

Image::~Image()
{
}

PixelType Image::getPixelType() const
{
    return _pixelType;
}

const std::vector<char>& Image::getData() const
{
    return _data;
}

int Image::getWidth() const
{
    return _width;
}

int Image::getHeight() const
{
    return _height;
}