#include "PhysicsRenderingDecorator.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;

PhysicsRenderingDecorator::PhysicsRenderingDecorator(std::shared_ptr<IPhysicsService> physicsService, std::shared_ptr<IRenderingStrategy> strategy, PhysicsFlags physicsFlags)
    : _physicsService(physicsService),
      _strategy(strategy),
      _physicsFlags(physicsFlags)
{
}

void PhysicsRenderingDecorator::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    _strategy->render(activeCameraStrategy);
}

void PhysicsRenderingDecorator::setPosition(const Vector3df &position)
{
    _strategy->setPosition(position);

    _physicsService->setPosition(_strategy, _strategy->getAbsolutePosition());
}

void PhysicsRenderingDecorator::setRotation(const Vector3df &rotation)
{
    _strategy->setRotation(rotation);
}

void PhysicsRenderingDecorator::setScale(const Vector3df &scale)
{
    _strategy->setScale(scale);
}

const Vector3df &PhysicsRenderingDecorator::getPosition() const
{
    return _strategy->getPosition();
}

const Vector3df &PhysicsRenderingDecorator::getRotation() const
{
    return _strategy->getRotation();
}

const Vector3df &PhysicsRenderingDecorator::getScale() const
{
    return _strategy->getScale();
}

void PhysicsRenderingDecorator::setAbsolutePosition(const Vector3df &position)
{
    _strategy->setAbsolutePosition(position);
}

void PhysicsRenderingDecorator::setAbsoluteRotation(const Vector3df &rotation)
{
    _strategy->setAbsoluteRotation(rotation);
}

Vector3df PhysicsRenderingDecorator::getAbsolutePosition() const
{
    return _strategy->getAbsolutePosition();
}

Vector3df PhysicsRenderingDecorator::getAbsoluteRotation() const
{
    return _strategy->getAbsoluteRotation();
}

Vector3df PhysicsRenderingDecorator::getAbsoluteScale() const
{
    return _strategy->getAbsoluteScale();
}

const std::vector<std::shared_ptr<IRenderingStrategy>> &PhysicsRenderingDecorator::getChildren() const
{
    return _strategy->getChildren();
}

void PhysicsRenderingDecorator::addChild(std::shared_ptr<IRenderingStrategy> child)
{
    _strategy->addChild(child);
}

void PhysicsRenderingDecorator::removeChild(std::shared_ptr<IRenderingStrategy> child)
{
    _strategy->removeChild(child);
}

std::vector<float> PhysicsRenderingDecorator::getVertices() const
{
    return _strategy->getVertices();
}

const Matrix4x4f &PhysicsRenderingDecorator::getModelMatrix() const
{
    return _strategy->getModelMatrix();
}

void PhysicsRenderingDecorator::_updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated)
{
    _strategy->_updateModelMatrix(parentMatrix, isPrsUpdated);
}

void PhysicsRenderingDecorator::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    _strategy->_onAttachedToParent(parent);

    switch (_physicsFlags)
    {
    case PhysicsFlags::STATIC:
        _physicsService->addBox(_strategy, 0.f);
        break;
    case PhysicsFlags::DYNAMIC:
        _physicsService->addBox(_strategy, 1.f);
        break;
    }
}

void PhysicsRenderingDecorator::_onDetachedFromParent()
{
    _strategy->_onDetachedFromParent();
}
