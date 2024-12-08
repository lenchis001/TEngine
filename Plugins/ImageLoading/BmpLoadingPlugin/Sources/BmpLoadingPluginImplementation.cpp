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

std::shared_ptr<IPluginImage> BmpLoadingPluginImplementation::load(const std::string &path)
{
    BmpInfo info = {0};
    BmpGetInfo(&info, path.c_str());

    auto dataSize = info.height * info.stride;

    unsigned char *pBmpData = new unsigned char[dataSize];
    BmpLoadImage(pBmpData, &info, path.c_str());

    return std::make_shared<BmpPluginImage>(info.width, info.height, reinterpret_cast<char*>(pBmpData), dataSize);
}

std::shared_ptr<IImageLoadingPlugin> load() {
    return std::make_shared<BmpLoadingPluginImplementation>();
}