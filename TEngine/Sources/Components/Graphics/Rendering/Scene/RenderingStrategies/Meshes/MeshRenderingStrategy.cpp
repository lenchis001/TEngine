#include "GL/glew.h"

#include "MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes;

MeshRenderingStrategy::MeshRenderingStrategy(
    std::shared_ptr<IMeshService> meshService,
    std::shared_ptr<IPhysicsService> physicsService,
    std::shared_ptr<ITexturesService> textureService,
    OnDeleteCallback onDeleteCallback,
    const std::string &path)
    : PhysicsRenderingStrategyBase(physicsService, onDeleteCallback),
      _meshService(meshService),
      _textureService(textureService),
      _path(path)
{
    _renderableMesh = _meshService->take(_path);
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

        glUniform3fv(shape->getShapeColorShaderId(), 1, shape->getDiffuseColor().data());

        if (shape->getTextureId())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, shape->getTextureId());
        }

        glDrawElements(GL_TRIANGLES, shape->getVertices().size(), GL_UNSIGNED_INT, nullptr);

#ifdef TENGINE_DEBUG
        // check for errors
        GLenum error = glGetError();
        if (error != GL_NO_ERROR)
        {
            std::cerr << "OpenGL error during mesh rendering: " << error << std::endl;
        }
#endif

        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_UNIFORM_BUFFER, 0);
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
