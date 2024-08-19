#include "Texture.h"

using namespace TEngine::Components::Graphics::ImageLoading::Models;

Texture::Texture(void *data, int width, int height)
    : _data(data),
      _width(width),
      _height(height)
{
}

void *Texture::getData() const
{
    return _data;
}

int Texture::getWidth() const
{
    return _width;
}

int Texture::getHeight() const
{
    return _height;
}