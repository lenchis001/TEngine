#include "GL/glew.h"

#include "MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes;

MeshRenderingStrategy::MeshRenderingStrategy(
    std::shared_ptr<IMeshService> meshService,
    const std::string &path)
    : RenderingStrategyBase(),
      _meshService(meshService)
{
    _prepareMesh(path);
}

void MeshRenderingStrategy::render(
    const Matrix4x4f &vpMatrix,
    const Components::Graphics::Models::Vector3df &cameraPosition)
{
    RenderingStrategyBase::render(vpMatrix, cameraPosition);

    for (auto &shape : _renderableMesh->getShapes())
    {
        glBindVertexArray(shape->getVAO());

        glUseProgram(shape->getProgram());
        glUniformMatrix4fv(shape->getMvpShaderId(), 1, GL_FALSE, getMvpMatrix().getInternalData());

        glDrawArrays(GL_TRIANGLES, 0, shape->getVerticesCount());

        glUseProgram(0);
        glBindVertexArray(0);
    }
}

void MeshRenderingStrategy::_prepareMesh(const std::string &path)
{
    _renderableMesh = _meshService->take(path);
}