#include "ImageLoadingService.h"

#include <cassert>

#define TENGINE_IMAGE_LOADING_DIRECTORY "Plugins/ImageLoading"

using namespace TEngine::Components::Graphics::ImageLoading::Services;

ImageLoadingService::ImageLoadingService(
#ifdef __ANDROID__
    GameActivity *gameActivity,
#endif
    std::shared_ptr<IFileService> fileService)
    : PluginsLoadingAware(
#ifdef __ANDROID__
    gameActivity
#endif
    ),
    _fileService(fileService)

{
}

ImageLoadingService::~ImageLoadingService()
{
}

void ImageLoadingService::initialize()
{
    _initialize(TENGINE_IMAGE_LOADING_DIRECTORY);
}

std::shared_ptr<Image> ImageLoadingService::load(const std::string &path)
{
    auto plugin = _getPlugin(path);
    
    auto data = _fileService->readAsBytes(path);

    auto result = plugin->load(data);

    auto enginePixelType = _toEnginePixelType(result->getPixelType());

    return std::make_shared<Image>(enginePixelType, result->getData(), result->getWidth(), result->getHeight());
}

EnginePixelType ImageLoadingService::_toEnginePixelType(PluginPixelType pluginPixelType)
{
    switch (pluginPixelType)
    {
    case PluginPixelType::RGB:
        return EnginePixelType::RGB;
    case PluginPixelType::RGBA:
        return EnginePixelType::RGBA;
    default:
        assert(false && "Unknown pixel type!");
        return EnginePixelType::RGB;
    }
}