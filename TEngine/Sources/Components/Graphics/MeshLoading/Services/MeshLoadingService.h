#ifndef TENGINE_MESHLOADINGSERVICE_H
#define TENGINE_MESHLOADINGSERVICE_H

#include "IMeshLoadingService.h"

#include <map>

#include "Mixins/PluginsLoadingAware.hpp"

#include "Components/Graphics/MeshLoading/Plugin/IMeshLoadingPlugin.h"

using namespace TEngine::Mixins;

using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Plugin;

namespace TEngine::Components::Graphics::MeshLoading::Services
{
    class MeshLoadingService : public PluginsLoadingAware<IMeshLoadingPlugin>, public IMeshLoadingService
    {
    public:
        MeshLoadingService(
#ifdef __ANDROID__
            GameActivity *gameActivity
#endif
        );

        void initialize() override;

        std::shared_ptr<IMesh> load(const std::string &path) override;

    private:
        std::shared_ptr<IMesh> _toMesh(std::shared_ptr<IPluginMesh> pluginMesh);

        std::shared_ptr<IShape> _toShape(std::shared_ptr<IPluginShape> pluginShape, unsigned int index);
    };
}

#endif // TENGINE_MESHLOADINGSERVICE_H