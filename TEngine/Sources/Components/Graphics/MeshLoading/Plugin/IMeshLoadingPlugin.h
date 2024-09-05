#ifndef TENGINE_MESHLOADING_PLUGIN_IMESHLOADINGPLUGIN_H
#define TENGINE_MESHLOADING_PLUGIN_IMESHLOADINGPLUGIN_H

#include "vector"
#include "memory"
#include "string"

#include "IPluginMesh.h"

namespace TEngine::Components::Graphics::MeshLoading::Plugin
{
    class IMeshLoadingPlugin
    {
    public:
        virtual ~IMeshLoadingPlugin() = default;

        virtual std::vector<std::string> getSupportedExtensions() const = 0;

        virtual std::shared_ptr<IPluginMesh> load(const std::string &path) = 0;
    };
}

#endif // TENGINE_MESHLOADING_PLUGIN_IMESHLOADINGPLUGIN_H