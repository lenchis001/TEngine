#ifndef OBJ_LOADING_PLUGIN_H
#define OBJ_LOADING_PLUGIN_H

#include "IMeshLoadingPlugin.h"

using namespace TEngine::Components::Graphics::MeshLoading::Plugin;

namespace ObjLoadingPlugin
{
    class ObjLoadingPluginImplementation : public IMeshLoadingPlugin
    {
    public:
        ObjLoadingPluginImplementation();
        virtual ~ObjLoadingPluginImplementation() override;

        virtual std::vector<std::string> getSupportedExtensions() const override;

        virtual std::shared_ptr<IPluginMesh> load(const std::vector<uint8_t>& data, const std::string& basePath) override;
    };
}

extern "C"
{
    std::shared_ptr<IMeshLoadingPlugin> load();
}

#endif // OBJ_LOADING_PLUGIN_H