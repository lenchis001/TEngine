#include "BmpPluginImage.h"

using namespace BmpImageLoadingPlugin::Models;

BmpPluginImage::BmpPluginImage(int width, int height, void *data, unsigned int dataSize)
    : _width(width), _height(height), _data(data), _dataSize(dataSize)
{
}

BmpPluginImage::~BmpPluginImage()
{
    delete[] _data;
}

unsigned int BmpPluginImage::getDataSize() const
{
    return _dataSize;
}

void *BmpPluginImage::getData() const
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