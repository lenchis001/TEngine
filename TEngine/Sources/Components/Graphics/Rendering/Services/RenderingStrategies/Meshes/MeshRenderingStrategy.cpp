#include "GL/glew.h"

#include "MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes;

MeshRenderingStrategy::MeshRenderingStrategy(
    std::shared_ptr<IMeshService> meshService,
    std::shared_ptr<ILightServices> lightServices,
    const std::string &path)
    : RenderingStrategyBase(),
      _meshService(meshService),
      _lightServices(lightServices)
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

        auto pointLight = _lightServices->getPointLight();

        auto m = pointLight->getPosition().getInternalData();
        glUniform3fv(shape->getLightPosShaderId(), 1, pointLight->getPosition().getInternalData());

        glUniform3fv(shape->getLightColorShaderId(), 1, pointLight->getDiffuseColor().getInternalData());

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
