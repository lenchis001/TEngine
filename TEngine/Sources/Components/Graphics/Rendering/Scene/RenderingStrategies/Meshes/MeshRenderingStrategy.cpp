#include "GL/glew.h"

#include "MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes;

MeshRenderingStrategy::MeshRenderingStrategy(
    std::shared_ptr<IMeshService> meshService,
    std::shared_ptr<ILightService> lightServices,
    std::shared_ptr<IPhysicsService> physicsService,
    std::shared_ptr<ITexturesService> textureService,
    OnDeleteCallback onDeleteCallback,
    const std::string &path)
    : PhysicsRenderingStrategyBase(physicsService, onDeleteCallback),
      LightRenderingStrategyBase(lightServices),
      _meshService(meshService),
      _textureService(textureService),
      _path(path),
      _size(0, 0, 0)
{
    _renderableMesh = _meshService->take(_path);

    _size = _determineSize(_getVertices());
}

MeshRenderingStrategy::~MeshRenderingStrategy()
{
    _meshService->release(_renderableMesh);
}

std::type_index MeshRenderingStrategy::getType() const
{
    return std::type_index(typeid(MeshRenderingStrategy));
}

void MeshRenderingStrategy::setPosition(const Vector3df &position)
{
    PhysicsRenderingStrategyBase::setPosition(position);
}

void MeshRenderingStrategy::setRotation(const Vector3df &rotation)
{
    PhysicsRenderingStrategyBase::setRotation(rotation);
}

const std::string &MeshRenderingStrategy::getPath() const
{
    return _path;
}

RenderingPriority MeshRenderingStrategy::getRenderingPriority() const
{
    bool hasTexture = false;

    for (const auto &shape : _renderableMesh->getShapes())
    {
        if (shape->getTextureId())
        {
            hasTexture = true;

            if (_textureService->isAlphaChannelAware(shape->getTextureId()))
            {
                return RenderingPriority::LOW;
            }
        }
    }

    return hasTexture ? RenderingPriority::HIGH : RenderingPriority::NONE;
}

const Vector3df &MeshRenderingStrategy::getSize() const
{
    return _size;
}

std::string MeshRenderingStrategy::_getDefaultName() const
{
    return "Mesh";
}

void MeshRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    const auto &viewMatrix = activeCameraStrategy->getViewMatrix();

    for (auto &shape : _renderableMesh->getShapes())
    {
        glBindVertexArray(shape->getVAO());
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, shape->getIndexBuffer());

        glUseProgram(shape->getProgram());
        glUniformMatrix4fv(shape->getMvpMatrixShaderId(), 1, GL_FALSE, getMvpMatrix().getInternalData());
        glUniformMatrix4fv(shape->getModelMatrixShaderId(), 1, GL_FALSE, getModelMatrix().getInternalData());
        glUniformMatrix4fv(shape->getViewMatrixShaderId(), 1, GL_FALSE, viewMatrix.getInternalData());


        auto& pointLights = getPointLights();
        auto& pointLight = pointLights[0];
        // auto pointLight = _lightServices->getPointLight();

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

        glDrawElements(GL_TRIANGLES, shape->getVertices().size(), GL_UNSIGNED_INT, nullptr);

        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }
}

std::vector<float> MeshRenderingStrategy::_getVertices() const
{
    std::vector<float> allVertices;

    for (const auto &shape : _renderableMesh->getShapes())
    {
        allVertices.insert(allVertices.end(), shape->getVertices().begin(), shape->getVertices().end());
    }

    return allVertices;
}

void MeshRenderingStrategy::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    PhysicsRenderingStrategyBase::_onAttachedToParent(parent);
}

void MeshRenderingStrategy::_onDetachedFromParent()
{
    PhysicsRenderingStrategyBase::_onDetachedFromParent();
}
