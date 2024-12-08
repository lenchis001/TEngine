#include "PngPluginImage.h"

using namespace PngLoadingPlugin::Models;

PngPluginImage::PngPluginImage(int width, int height, char *data, unsigned int dataSize)
    : _width(width), _height(height), _data(data), _dataSize(dataSize)
{
}

PngPluginImage::~PngPluginImage()
{
    delete[] _data;
}

PixelType PngPluginImage::getPixelType() const
{
    return PixelType::RGBA;
}

unsigned int PngPluginImage::getDataSize() const
{
    return _dataSize;
}

char *PngPluginImage::getData() const
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