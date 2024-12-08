#include "Image.h"

#include <cstring>

using namespace TEngine::Components::Graphics::ImageLoading::Models;

Image::Image(PixelType pixelType, char *data, unsigned int dataSize, int width, int height)
    : _pixelType(pixelType),
      _dataSize(dataSize),
      _width(width),
      _height(height)
{
    _data = new char[dataSize];
    memcpy(_data, data, dataSize);
}

Image::~Image()
{
    delete[] _data;
}

PixelType Image::getPixelType() const
{
    return _pixelType;
}

char *Image::getData() const
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