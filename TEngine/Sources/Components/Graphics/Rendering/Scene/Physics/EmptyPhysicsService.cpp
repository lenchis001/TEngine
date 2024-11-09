#include "EmptyPhysicsService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;

void EmptyPhysicsService::initialize()
{
}

void EmptyPhysicsService::update(double time)
{
}

void EmptyPhysicsService::addBox(std::shared_ptr<IRenderingStrategy> renderingStrategy, float mass) {}

void EmptyPhysicsService::removeBox(
    std::shared_ptr<IRenderingStrategy> renderingStrategy) {}

void EmptyPhysicsService::setPosition(
    const std::shared_ptr<IRenderingStrategy> renderingStrategy,
    const Vector3df &position) {}

void EmptyPhysicsService::setRotation(
    const std::shared_ptr<IRenderingStrategy> renderingStrategy,
    const Vector3df &rotation) {}