#include "GL/glew.h"

#include "MeshService.h"

#include "Components/Graphics/Rendering/Models/Meshes/RenderableMesh.h"
#include "Components/Graphics/Rendering/Models/Meshes/RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Meshes;

MeshService::MeshService(
    std::shared_ptr<IMeshLoadingService> meshLoadingService,
    std::shared_ptr<IBuffersService> buffersService)
    : _meshLoadingService(meshLoadingService), _buffersService(buffersService)
{
}

std::shared_ptr<IRenderableMesh> MeshService::load(const std::string &path)
{
    auto mesh = _meshLoadingService->load(path);

    std::vector<std::shared_ptr<IRenderableShape>> renderableShapes;

    for (auto &shape : mesh->getShapes())
    {
        renderableShapes.push_back(_toRenderableShape(shape, path));
    }

    return std::make_shared<RenderableMesh>(renderableShapes);
}

std::shared_ptr<IRenderableShape> MeshService::_toRenderableShape(std::shared_ptr<IShape> shape, const std::string& path)
{
    // Prepare vertices VBO
    auto verticesBufferName = path + shape->getName() + "Vertices";

    auto verticesBuffer = _buffersService->takeVbo(verticesBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);

    const auto& vertices = shape->getVertices();
    auto verticesCount = vertices.size();
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Prepare VAO
    auto vao = _buffersService->takeVao(path + shape->getName());

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);

    return std::make_shared<RenderableShape>(vao, verticesCount);
}