#include "Image.h"

using namespace TEngine::Components::Graphics::ImageLoading::Models;

Image::Image(void *data, int width, int height)
    : _data(data),
      _width(width),
      _height(height)
{
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