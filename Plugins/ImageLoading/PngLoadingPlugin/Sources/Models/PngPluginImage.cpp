#include "PngPluginImage.h"

using namespace PngLoadingPlugin::Models;

PngPluginImage::PngPluginImage(int width, int height, const std::vector<char>& data)
    : _width(width), _height(height), _data(data)
{
}

PngPluginImage::~PngPluginImage()
{
}

PixelType PngPluginImage::getPixelType() const
{
    return PixelType::RGBA;
}

const std::vector<char>& PngPluginImage::getData() const
{
    return _data;
}

int PngPluginImage::getWidth() const
{
    return _width;
}

int PngPluginImage::getHeight() const
{
    return _height;
}