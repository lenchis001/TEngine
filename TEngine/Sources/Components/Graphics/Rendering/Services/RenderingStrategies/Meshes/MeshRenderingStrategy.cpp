#include "gl/glew.h"

#include "MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes;

MeshRenderingStrategy::MeshRenderingStrategy(std::shared_ptr<IMeshService> meshService)
    : RenderingStrategyBase(), _meshService(meshService)
{
}

void MeshRenderingStrategy::render(
    const Matrix4x4f &vpMatrix,
    const Components::Graphics::Models::Vector3df &cameraPosition)
{
    RenderingStrategyBase::render(vpMatrix, cameraPosition);

    for (auto &shape : _renderableMesh->getShapes())
    {
        glBindVertexArray(shape->getVAO());

        glDrawArrays(GL_TRIANGLES, 0, shape->getVerticesCount() / 3);

        glBindVertexArray(0);
    }
}

void MeshRenderingStrategy::_prepareMesh()
{
    
}