#include "BmpImageLoadingPlugin.h"

#include "libbmp/bmp.h"

BmpImageLoadingPlugin::BmpImageLoadingPlugin()
{
}

BmpImageLoadingPlugin::~BmpImageLoadingPlugin()
{
}

std::vector<std::string> BmpImageLoadingPlugin::getSupportedExtensions() const
{
    return std::vector<std::string>{"bmp"};
}

std::shared_ptr<IPluginImage> BmpImageLoadingPlugin::load(const std::string &path)
{
    BmpInfo info = {0};
    BmpGetInfo(&info, path.c_str());

    unsigned char *pBmpData = new unsigned char[info.height * info.stride];
    BmpLoadImage(pBmpData, &info, path.c_str());

    BmpSaveImage(pBmpData, &info, "D:/test.bmp");

    return nullptr;
}

std::shared_ptr<IImageLoadingPlugin> load()
{
    return std::make_shared<BmpImageLoadingPlugin>();
}