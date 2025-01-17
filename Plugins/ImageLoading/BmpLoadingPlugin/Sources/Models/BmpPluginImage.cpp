#include "BmpPluginImage.h"

using namespace BmpLoadingPlugin::Models;

BmpPluginImage::BmpPluginImage(int width, int height, const std::vector<char>& data)
    : _width(width), _height(height), _data(data)
{
}

BmpPluginImage::~BmpPluginImage()
{
}

PixelType BmpPluginImage::getPixelType() const
{
    return PixelType::RGB;
}

const std::vector<char>& BmpPluginImage::getData() const
{
    return _data;
}

int BmpPluginImage::getWidth() const
{
    return _width;
}

int BmpPluginImage::getHeight() const
{
    return _height;
}