#ifndef TENGINE_IPHYSICSSERVICE_H
#define TENGINE_IPHYSICSSERVICE_H

#include <vector>
#include <memory>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics
{
    class IPhysicsService
    {
    public:
        virtual ~IPhysicsService() = default;

        virtual void initialize() = 0;

        virtual void update(double time) = 0;

        virtual void addStaticBox(
            const Graphics::Models::Vector3df &size,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> renderingStrategy
            ) = 0;

        virtual void addDynamicBox(
            const Graphics::Models::Vector3df &size,
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> renderingStrategy
            ) = 0;

        virtual void setPosition(
            const std::shared_ptr<RenderingStrategies::IRenderingStrategy> renderingStrategy,
            const Graphics::Models::Vector3df &position
            ) = 0;
    };
}

#endif // TENGINE_IPHYSICSSERVICE_H