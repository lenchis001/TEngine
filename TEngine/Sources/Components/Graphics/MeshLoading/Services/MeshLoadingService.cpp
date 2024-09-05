#include "MeshLoadingService.h"

#include "Components/Graphics/MeshLoading/Models/Shape.h"
#include "Components/Graphics/MeshLoading/Models/Mesh.h"

#define TENGINE_MESH_LOADING_DIRECTORY "Plugins/MeshLoading"

using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Services;

MeshLoadingService::MeshLoadingService()
{
}

void MeshLoadingService::initialize()
{
    _initialize(TENGINE_MESH_LOADING_DIRECTORY);
}

std::shared_ptr<IMesh> MeshLoadingService::load(const std::string &path)
{
    auto plugin = _load(path);

    auto pluginMesh = plugin->load(path);

    return _toMesh(pluginMesh);
}

std::shared_ptr<IMesh> MeshLoadingService::_toMesh(std::shared_ptr<IPluginMesh> pluginMesh)
{
    std::vector<std::shared_ptr<IShape>> shapes;

    for (auto &pluginShape : pluginMesh->getShapes())
    {
        shapes.push_back(_toShape(pluginShape));
    }

    return std::make_shared<Mesh>(shapes);
}

std::shared_ptr<IShape> MeshLoadingService::_toShape(std::shared_ptr<IPluginShape> pluginShape)
{
    // todo: use move
    return std::make_shared<Shape>(
        pluginShape->getName(),
        pluginShape->getVertices(),
        pluginShape->getTextures(),
        pluginShape->getNormals(),
        pluginShape->getUVs());
}