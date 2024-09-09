#ifndef TENGINE_IRENDERINGSTRATEGY_H
#define TENGINE_IRENDERINGSTRATEGY_H

#include "memory"
#include "vector"

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Models/Matrix4x4.h"
#include "Components/Graphics/Rendering/Services/CameraStrategies/ICameraStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies
{
    class RenderingStrategyBase;
    class RenderingOptimizationDecorator;

    class IRenderingStrategy
    {
    public:
        virtual void render(std::shared_ptr<Graphics::Rendering::Services::CameraStrategies::ICameraStrategy> activeCameraStrategy) = 0;

        virtual void setPosition(const Graphics::Models::Vector3df &position) = 0;
        virtual void setRotation(const Graphics::Models::Vector3df &rotation) = 0;
        virtual void setScale(const Graphics::Models::Vector3df &scale) = 0;

        virtual const Graphics::Models::Vector3df &getPosition() const = 0;
        virtual const Graphics::Models::Vector3df &getRotation() const = 0;
        virtual const Graphics::Models::Vector3df &getScale() const = 0;

        virtual Graphics::Models::Vector3df getAbsolutePosition() = 0;

        virtual const std::vector<std::shared_ptr<IRenderingStrategy>> &getChildren() const = 0;
        virtual void addChild(std::shared_ptr<IRenderingStrategy> child) = 0;
        virtual void removeChild(std::shared_ptr<IRenderingStrategy> child) = 0;

        virtual ~IRenderingStrategy() = default;

        friend RenderingStrategyBase;
        friend RenderingOptimizationDecorator;

    protected:
        virtual void _updateModelMatrix(const Components::Graphics::Models::Matrix4x4f &parentMatrix, bool isPrsUpdated = false) = 0;
    };
}

#endif // TENGINE_IRENDERINGSTRATEGY_H