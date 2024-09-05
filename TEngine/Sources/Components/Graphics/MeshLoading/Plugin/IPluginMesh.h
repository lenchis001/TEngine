#ifndef TENGINE_MESHLOADING_PLUGIN_IPLUGINMESH_H
#define TENGINE_MESHLOADING_PLUGIN_IPLUGINMESH_H

#include "vector"
#include "memory"

#include "IPluginShape.h"

namespace TEngine::Components::Graphics::MeshLoading::Plugin
{
    class IPluginMesh
    {
    public:
        virtual ~IPluginMesh() = default;

        virtual const std::vector<std::shared_ptr<IPluginShape>> &getShapes() const = 0;
    };
}

#endif // TENGINE_MESHLOADING_PLUGIN_IPLUGINMESH_H