#include "ImageLoadingService.h"

#define TENGINE_IMAGE_LOADING_DIRECTORY "Plugins/ImageLoading"

using namespace TEngine::Components::Graphics::ImageLoading::Services;

ImageLoadingService::~ImageLoadingService()
{
}

void ImageLoadingService::initialize()
{
    _initialize(TENGINE_IMAGE_LOADING_DIRECTORY);
}

std::shared_ptr<Image> ImageLoadingService::load(const std::string &path)
{
    auto plugin = _load(path);

    auto result = plugin->load(path);

    return std::make_shared<Image>(result->getData(), result->getDataSize(), result->getWidth(), result->getHeight());
}