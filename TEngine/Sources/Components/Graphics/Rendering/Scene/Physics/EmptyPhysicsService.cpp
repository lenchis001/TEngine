#include "EmptyPhysicsService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;

void EmptyPhysicsService::initialize()
{
}

void EmptyPhysicsService::update(double time)
{
}

bool EmptyPhysicsService::isAttached(
    std::shared_ptr<IPhysicsRenderingAware> renderingStrategy)
{
    return false;
}

void EmptyPhysicsService::addBox(std::shared_ptr<IPhysicsRenderingAware> renderingStrategy, float mass) {}

void EmptyPhysicsService::removeBox(
    std::shared_ptr<IPhysicsRenderingAware> renderingStrategy) {}

void EmptyPhysicsService::setPosition(
    const std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
    const Vector3df &position) {}

void EmptyPhysicsService::setRotation(
    const std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
    const Vector3df &rotation) {}