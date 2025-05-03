#include "BmpLoadingPluginImplementation.h"

#include "libbmp/bmp.h"

#include "Models/BmpPluginImage.h"

using namespace BmpLoadingPlugin;
using namespace BmpLoadingPlugin::Models;

BmpLoadingPluginImplementation::BmpLoadingPluginImplementation()
{
}

BmpLoadingPluginImplementation::~BmpLoadingPluginImplementation()
{
}

std::vector<std::string> BmpLoadingPluginImplementation::getSupportedExtensions() const
{
    return std::vector<std::string>{"bmp"};
}

std::shared_ptr<IPluginImage> BmpLoadingPluginImplementation::load(const std::vector<uint8_t>& data)
{
    BmpInfo info = {0};
    BmpGetInfoFromMemory(&info, data);

    auto dataSize = info.height * info.stride;

    unsigned char *pBmpData = new unsigned char[dataSize];
    BmpLoadImageFromMemory(pBmpData, &info, data);

    std::vector<char> imageData(dataSize);
    imageData.assign(pBmpData, pBmpData + dataSize);

    return std::make_shared<BmpPluginImage>(info.width, info.height, imageData);
}

std::shared_ptr<IImageLoadingPlugin> load() {
    return std::make_shared<BmpLoadingPluginImplementation>();
}