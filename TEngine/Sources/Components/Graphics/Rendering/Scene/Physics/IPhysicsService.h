#ifndef TENGINE_IPHYSICSSERVICE_H
#define TENGINE_IPHYSICSSERVICE_H

#include <vector>
#include <memory>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Physics/IPhysicsRenderingAware.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Physics
{
    class IPhysicsService
    {
    public:
        virtual ~IPhysicsService() = default;

        virtual void initialize() = 0;

        virtual void update(double time) = 0;

        virtual bool isAttached(std::shared_ptr<Scene::RenderingStrategies::Physics::IPhysicsRenderingAware> renderingStrategy) = 0;

        virtual void addBox(
            std::shared_ptr<Scene::RenderingStrategies::Physics::IPhysicsRenderingAware> renderingStrategy,
            float mass
            ) = 0;

        virtual void removeBox(
            std::shared_ptr<Scene::RenderingStrategies::Physics::IPhysicsRenderingAware> renderingStrategy
            ) = 0;

        virtual void setPosition(
            const std::shared_ptr<Scene::RenderingStrategies::Physics::IPhysicsRenderingAware> renderingStrategy,
            const Graphics::Models::Vector3df &position
            ) = 0;

        virtual void setRotation(
            const std::shared_ptr<Scene::RenderingStrategies::Physics::IPhysicsRenderingAware> renderingStrategy,
            const Graphics::Models::Vector3df &rotation
            ) = 0;

    };
}

#endif // TENGINE_IPHYSICSSERVICE_H