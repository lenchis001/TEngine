#include "Image.h"

#include <cstring>

using namespace TEngine::Components::Graphics::ImageLoading::Models;

Image::Image(void *data, unsigned int dataSize, int width, int height)
    : _dataSize(dataSize),
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

void *Image::getData() const
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