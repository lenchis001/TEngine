#include "MeshLoadingService.h"

#include <iostream>

#include <boost/filesystem.hpp>

#include "Components/Graphics/MeshLoading/Models/Shape.h"
#include "Components/Graphics/MeshLoading/Models/Mesh.h"

#define TENGINE_MESH_LOADING_DIRECTORY "Plugins/MeshLoading"

using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Services;

MeshLoadingService::MeshLoadingService(
#ifdef __ANDROID__
    GameActivity *gameActivity,
#endif
    std::shared_ptr<IFileService> fileService
    ):
#ifdef __ANDROID__ 
    PluginsLoadingAware(gameActivity),
#endif
    _fileService(fileService)
{
}

void MeshLoadingService::initialize()
{
    _initialize(TENGINE_MESH_LOADING_DIRECTORY);
}

std::shared_ptr<IMesh> MeshLoadingService::load(const std::string &path)
{
    auto plugin = _getPlugin(path);

    auto data = _fileService->readAsBytes(path);

    auto absolutePath = _fileService->toAbsolutePath(path);
    auto parentDirectory = boost::filesystem::path(absolutePath).parent_path().string();

    auto pluginMesh = plugin->load(data, parentDirectory);

    for(const auto& shape : pluginMesh->getShapes())
    {
        std::cout << "Shape name: " << shape->getName() << std::endl;
        std::cout << "Vertices count: " << shape->getVertices().size() / 3 << std::endl;
        std::cout << "Normals count: " << shape->getNormals().size() / 3 << std::endl;
        std::cout << "UVs count: " << shape->getUVs().size() / 2 << std::endl;
        std::cout << "Diffuse color: " << shape->getDiffuseColor()[0] << ", " << shape->getDiffuseColor()[1] << ", " << shape->getDiffuseColor()[2] << std::endl;
        std::cout << "Texture path: " << shape->getTexturePath() << std::endl;
        std::cout << "------------------------" << std::endl;
    }
    
    
    return _toMesh(pluginMesh);
}

std::shared_ptr<IMesh> MeshLoadingService::_toMesh(std::shared_ptr<IPluginMesh> pluginMesh)
{
    std::vector<std::shared_ptr<IShape>> shapes;

    unsigned int i = 0;
    for (auto &pluginShape : pluginMesh->getShapes())
    {
        shapes.push_back(_toShape(pluginShape, i++));
    }

    return std::make_shared<Mesh>(shapes);
}

std::shared_ptr<IShape> MeshLoadingService::_toShape(std::shared_ptr<IPluginShape> pluginShape, unsigned int index)
{
    auto name = pluginShape->getName();

    if (name.empty())
    {
        name = "Shape:" + std::to_string(index);
    }

    auto normalsCount = pluginShape->getNormals().size();

    // todo: use move
    return std::make_shared<Shape>(
        name,
        pluginShape->getVertices(),
        pluginShape->getNormals(),
        pluginShape->getUVs(),
        pluginShape->getDiffuseColor(),
        pluginShape->getTexturePath());
}