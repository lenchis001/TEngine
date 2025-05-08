#ifndef OBJ_PLUGIN_MESH_H
#define OBJ_PLUGIN_MESH_H

#include "IPluginMesh.h"

using namespace TEngine::Components::Graphics::MeshLoading::Plugin;

namespace ObjLoadingPlugin::Models
{
    class ObjPluginMesh : public IPluginMesh
    {
    public:
        ObjPluginMesh(const std::vector<std::shared_ptr<IPluginShape>>& shapes);
        ~ObjPluginMesh() override;
        
        const std::vector<std::shared_ptr<IPluginShape>> &getShapes() const override;
    private:
        std::vector<std::shared_ptr<IPluginShape>> _shapes;
    };
}

#endif // OBJ_PLUGIN_MESH_H