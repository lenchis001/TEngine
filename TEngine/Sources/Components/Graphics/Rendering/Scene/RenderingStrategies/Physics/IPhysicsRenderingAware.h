#ifndef TENGINE_IPHYSICSRENDERINGAWARE_H
#define TENGINE_IPHYSICSRENDERINGAWARE_H

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/Models/Physics/PhysicsFlags.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Physics
{
    class PhysicsService;
}

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Physics
{
    class IPhysicsRenderingAware : public virtual IRenderingStrategy
    {
    public:
        virtual void setPhysicsFlags(Models::Physics::PhysicsFlags physicsFlags) = 0;

        virtual Models::Physics::PhysicsFlags getPhysicsFlags() const = 0;

        friend Scene::Physics::PhysicsService;

    protected:
        virtual std::vector<float> getVertices() const = 0;

        virtual void setDirectAbsolutePosition(const Graphics::Models::Vector3df &position) = 0;

        virtual void setDirectAbsoluteRotation(const Graphics::Models::Vector3df &rotation) = 0;
    };
}

#endif // TENGINE_IPHYSICSRENDERINGAWARE_H