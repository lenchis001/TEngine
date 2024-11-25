#include "PhysicsRenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingMixins;

PhysicsRenderingStrategyBase::PhysicsRenderingStrategyBase(std::shared_ptr<IPhysicsService> physicsService)
    : _physicsService(physicsService),
      _physicsFlags(PhysicsFlags::NONE),
      _isAttachedToParent(false)
{
}

void PhysicsRenderingStrategyBase::setPosition(const Vector3df &position)
{
    if (_isPhysicsEnabled())
    {
        auto newAbsolutePosition = _parentMatrix.getPosition() + position;

        _physicsService->setPosition(_getSharedPhysicsRenderingAware(), newAbsolutePosition);
    }
    else
    {
        RenderingStrategyBase::setPosition(position);
    }
}

void PhysicsRenderingStrategyBase::setRotation(const Vector3df &rotation)
{
    if (_isPhysicsEnabled())
    {
        auto newAbsoluteRotation = _parentMatrix.getRotation() + rotation;

        _physicsService->setRotation(_getSharedPhysicsRenderingAware(), newAbsoluteRotation);
    }
    else
    {
        RenderingStrategyBase::setRotation(rotation);
    }
}

void PhysicsRenderingStrategyBase::setScale(const Vector3df &scale)
{
    RenderingStrategyBase::setScale(scale);

    if (_isPhysicsEnabled() && _physicsService->isAttached(_getSharedPhysicsRenderingAware()))
    {
        _physicsService->removeBox(_getSharedPhysicsRenderingAware());

        _attachToPhysics();
    }
}

PhysicsFlags PhysicsRenderingStrategyBase::getPhysicsFlags() const
{
    return _physicsFlags;
}

void PhysicsRenderingStrategyBase::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    RenderingStrategyBase::_onAttachedToParent(parent);

    _isAttachedToParent = true;

    if (_isPhysicsEnabled())
    {
        _attachToPhysics();
    }
}

void PhysicsRenderingStrategyBase::_onDetachedFromParent()
{
    _isAttachedToParent = false;

    if (_physicsService->isAttached(_getSharedPhysicsRenderingAware()))
    {
        _physicsService->removeBox(_getSharedPhysicsRenderingAware());
    }

    RenderingStrategyBase::_onDetachedFromParent();
}

void PhysicsRenderingStrategyBase::setPhysicsFlags(PhysicsFlags physicsFlags)
{
    auto sharedThisPhysicsRenderingAware = _getSharedPhysicsRenderingAware();

    if (_physicsService->isAttached(sharedThisPhysicsRenderingAware))
    {
        _physicsService->removeBox(sharedThisPhysicsRenderingAware);
    }

    _physicsFlags = physicsFlags;

    if (_isPhysicsEnabled())
    {
        _attachToPhysics();
    }
}

bool PhysicsRenderingStrategyBase::_isPhysicsEnabled() const
{
    return _physicsFlags != PhysicsFlags::NONE && _isAttachedToParent;
}

void PhysicsRenderingStrategyBase::_attachToPhysics()
{
    switch (_physicsFlags)
    {
    case PhysicsFlags::STATIC:
        _physicsService->addBox(_getSharedPhysicsRenderingAware(), 0.f);
        break;
    case PhysicsFlags::DYNAMIC:
        _physicsService->addBox(_getSharedPhysicsRenderingAware(), 1.f);
        break;
    default:
        break;
    }

    if (_isPhysicsEnabled())
    {
        _physicsService->setPosition(_getSharedPhysicsRenderingAware(), getAbsolutePosition());
        _physicsService->setRotation(_getSharedPhysicsRenderingAware(), getAbsoluteRotation());
    }
}

std::shared_ptr<IPhysicsRenderingAware> PhysicsRenderingStrategyBase::_getSharedPhysicsRenderingAware()
{
    auto renderingStrategy = shared_from_this();

    return std::dynamic_pointer_cast<IPhysicsRenderingAware>(renderingStrategy);
}

std::vector<float> PhysicsRenderingStrategyBase::getVertices() const
{
    auto modelVertices = _getVertices();
    auto scale = getScale();

    for (size_t i = 0; i < modelVertices.size(); i += 3)
    {
        modelVertices[i] *= scale.getX();
        modelVertices[i + 1] *= scale.getY();
        modelVertices[i + 2] *= scale.getZ();
    }

    return modelVertices;
}

void PhysicsRenderingStrategyBase::setDirectAbsolutePosition(const Vector3df &position)
{
    auto parentPosition = _parentMatrix.getPosition();

    auto diff = position - parentPosition;

    RenderingStrategyBase::setPosition(diff);
}

void PhysicsRenderingStrategyBase::setDirectAbsoluteRotation(const Vector3df &rotation)
{
    auto parentRotation = _parentMatrix.getRotation();

    auto diff = rotation - parentRotation;

    RenderingStrategyBase::setRotation(diff);
}