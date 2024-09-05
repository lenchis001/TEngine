#include "ObjPluginMesh.h"

using namespace ObjLoadingPlugin::Models;

ObjPluginMesh::ObjPluginMesh(const std::vector<std::shared_ptr<IPluginShape>>& shapes)
    : _shapes(shapes)
{
}

ObjPluginMesh::~ObjPluginMesh()
{
}

const std::vector<std::shared_ptr<IPluginShape>> &ObjPluginMesh::getShapes() const
{
    return _shapes;
}