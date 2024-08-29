#ifndef IMAGELOADINGSERVICE_H
#define IMAGELOADINGSERVICE_H

#include "string"
#include "vector"
#include "unordered_map"

#include "Components/Graphics/ImageLoading/Plugin/IImageLoadingPlugin.h"


#include "IImageLoadingService.h"
#include "PluginsLoadingAware.hpp"

using namespace TEngine::Components::Graphics::ImageLoading::Models;
using namespace TEngine::Components::Graphics::ImageLoading::Plugin;

namespace TEngine::Components::Graphics::ImageLoading::Services
{
    class ImageLoadingService : public PluginsLoadingAware, public IImageLoadingService
    {
    public:
        ImageLoadingService() = default;
        ~ImageLoadingService() override;

        void initialize() override;

        std::shared_ptr<Image> load(const std::string &path) override;

    private:
        std::vector<std::string> _findPlugins() const;
        std::shared_ptr<IImageLoadingPlugin> _loadPlugin(const std::string &path);

        std::unordered_map<std::string, std::shared_ptr<IImageLoadingPlugin>> _plugins;
        std::vector<DYNAMIC_LIB_HANDLE> _loadedLibraries;
    };
}

#endif // IMAGELOADINGSERVICE_H