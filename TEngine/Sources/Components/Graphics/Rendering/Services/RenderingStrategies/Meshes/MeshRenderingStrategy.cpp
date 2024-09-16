#include "GL/glew.h"

#include "MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes;

MeshRenderingStrategy::MeshRenderingStrategy(
    std::shared_ptr<IMeshService> meshService,
    const std::string &path)
    : RenderingStrategyBase(),
      _meshService(meshService)
{
    _renderableMesh = _meshService->take(path);
}

MeshRenderingStrategy::~MeshRenderingStrategy()
{
    _meshService->release(_renderableMesh);
}

void MeshRenderingStrategy::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    RenderingStrategyBase::render(activeCameraStrategy);

    const auto &viewMatrix = activeCameraStrategy->getViewMatrix();

    for (auto &shape : _renderableMesh->getShapes())
    {
        glBindVertexArray(shape->getVAO());

        glUseProgram(shape->getProgram());
        glUniformMatrix4fv(shape->getMvpMatrixShaderId(), 1, GL_FALSE, getMvpMatrix().getInternalData());
        glUniformMatrix4fv(shape->getModelMatrixShaderId(), 1, GL_FALSE, getModelMatrix().getInternalData());
        glUniformMatrix4fv(shape->getViewMatrixShaderId(), 1, GL_FALSE, viewMatrix.getInternalData());

        float lightPos[] = {0.0f, 7.0f, 10.0f};
        glUniform3fv(shape->getLightPosShaderId(), 1, lightPos);

        float lightColor[] = {1.0f, 1.0f, 1.0f};
        glUniform3fv(shape->getLightColorShaderId(), 1, lightColor);

        float lightPower = 50.0f;
        glUniform1f(shape->getLightPowerShaderId(), lightPower);

        glUniform3fv(shape->getShapeColorShaderId(), 1, shape->getDiffuseColor().data());

        if (shape->getTextureId())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, shape->getTextureId());
        }

        glDrawArrays(GL_TRIANGLES, 0, shape->getVerticesCount());

        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }
}
