#include "ImageLoadingService.h"

#include "filesystem"

#define TENGINE_IMAGE_LOADING_DIRECTORY "Plugins/ImageLoading"
#define LOAD_FUNCTION_NAME "load"

using namespace TEngine::Components::Graphics::ImageLoading::Services;

typedef std::shared_ptr<IImageLoadingPlugin> (*loadPluginDelegate)();

ImageLoadingService::~ImageLoadingService()
{
    for (const auto &lib : _loadedLibraries)
    {
        closeLibrary(lib);
    }
}

void ImageLoadingService::initialize()
{
    std::vector<std::string> plugins = _findPlugins();

    for (const auto &plugin : plugins)
    {
        std::shared_ptr<IImageLoadingPlugin> loadedPlugin = _loadPlugin(plugin);
        if (loadedPlugin)
        {
            for (const auto &extension : loadedPlugin->getSupportedExtensions())
            {
                _plugins[extension] = loadedPlugin;
            }
        }
    }
}

std::shared_ptr<Image> ImageLoadingService::load(const std::string &path)
{
    auto pluginIterator = _plugins.find("bmp");

    if(pluginIterator == _plugins.end()) {
        return nullptr;
    }

    auto result = pluginIterator->second->load(path);

    return std::make_shared<Image>(result->getData(), result->getDataSize(), result->getWidth(), result->getHeight());
}

std::vector<std::string> ImageLoadingService::_findPlugins() const
{
    std::vector<std::string> libraries;

    for (const auto &entry : std::filesystem::directory_iterator(TENGINE_IMAGE_LOADING_DIRECTORY))
    {
        std::string filename = entry.path().filename().string();
        if (filename.size() > 3 && (filename.substr(filename.size() - 3) == ".so" || filename.substr(filename.size() - 4) == ".dll" || filename.substr(filename.size() - 6) == ".dylib"))
        {
            libraries.push_back(entry.path().string());
        }
    }

    return libraries;
}

std::shared_ptr<IImageLoadingPlugin> ImageLoadingService::_loadPlugin(const std::string &path)
{
    auto lib = loadPlugins(path);

    auto function = getFunction(lib, LOAD_FUNCTION_NAME);
    auto delegate = reinterpret_cast<loadPluginDelegate>(function);

    auto plugin = delegate();
    return plugin;
}