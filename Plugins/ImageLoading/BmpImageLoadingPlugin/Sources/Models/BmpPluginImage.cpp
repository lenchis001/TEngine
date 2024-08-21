#include "BmpPluginImage.h"

using namespace BmpImageLoadingPlugin::Models;

BmpPluginImage::BmpPluginImage(int width, int height, void *data)
    : _width(width), _height(height), _data(data)
{
}

BmpPluginImage::~BmpPluginImage()
{
    delete[] _data;
}

void *BmpPluginImage::getData() const
{
    return nullptr;
}

int BmpPluginImage::getWidth() const
{
    return 0;
}

int BmpPluginImage::getHeight() const
{
    return 0;
}