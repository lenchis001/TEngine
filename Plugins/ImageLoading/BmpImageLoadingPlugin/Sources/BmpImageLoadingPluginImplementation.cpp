#include "BmpImageLoadingPluginImplementation.h"

#include "libbmp/bmp.h"

#include "Models/BmpPluginImage.h"

using namespace BmpImageLoadingPlugin;
using namespace BmpImageLoadingPlugin::Models;

BmpImageLoadingPluginImplementation::BmpImageLoadingPluginImplementation()
{
}

BmpImageLoadingPluginImplementation::~BmpImageLoadingPluginImplementation()
{
}

std::vector<std::string> BmpImageLoadingPluginImplementation::getSupportedExtensions() const
{
    return std::vector<std::string>{"bmp"};
}

std::shared_ptr<IPluginImage> BmpImageLoadingPluginImplementation::load(const std::string &path)
{
    BmpInfo info = {0};
    BmpGetInfo(&info, path.c_str());

    unsigned char *pBmpData = new unsigned char[info.height * info.stride];
    BmpLoadImage(pBmpData, &info, path.c_str());

    return std::make_shared<BmpPluginImage>(info.width, info.height, pBmpData);
}

std::shared_ptr<IImageLoadingPlugin> load() {
    return std::make_shared<BmpImageLoadingPluginImplementation>();
}