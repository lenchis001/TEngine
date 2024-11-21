#ifndef TENGINE_IRENDERINGSTRATEGY_H
#define TENGINE_IRENDERINGSTRATEGY_H

#include <memory>
#include <vector>

#include "Mixins/TypeInfoAware.h"

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Models/Matrix4x4.h"
#include "Components/Graphics/Rendering/Scene/CameraStrategies/ICameraStrategy.h"
#include "Components/Graphics/Rendering/Models/Physics/PhysicsFlags.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies
{
    class RenderingStrategyBase;
    class PhysicsRenderingDecorator;

    class IRenderingStrategy : public Mixins::TypeInfoAware
    {
    public:
        virtual void render(std::shared_ptr<Graphics::Rendering::Scene::CameraStrategies::ICameraStrategy> activeCameraStrategy) = 0;

        virtual void setPosition(const Graphics::Models::Vector3df &position) = 0;
        virtual void setRotation(const Graphics::Models::Vector3df &rotation) = 0;
        virtual void setScale(const Graphics::Models::Vector3df &scale) = 0;

        virtual const Graphics::Models::Vector3df &getPosition() const = 0;
        virtual const Graphics::Models::Vector3df &getRotation() const = 0;
        virtual const Graphics::Models::Vector3df &getScale() const = 0;

        virtual void setAbsolutePosition(const Graphics::Models::Vector3df &position) = 0;
        virtual void setAbsoluteRotation(const Graphics::Models::Vector3df &rotation) = 0;

        virtual Graphics::Models::Vector3df getAbsolutePosition() const = 0;
        virtual Graphics::Models::Vector3df getAbsoluteRotation() const = 0;
        virtual Graphics::Models::Vector3df getAbsoluteScale() const = 0;

        virtual const std::vector<std::shared_ptr<IRenderingStrategy>> &getChildren() const = 0;
        virtual void addChild(std::shared_ptr<IRenderingStrategy> child) = 0;
        virtual void removeChild(std::shared_ptr<IRenderingStrategy> child) = 0;
        virtual void removeAllChildren() = 0;
        
        virtual std::vector<float> getVertices() const = 0;

        virtual const std::string &getName() = 0;
        virtual void setName(const std::string &name) = 0;

        virtual int getId() const = 0;

        virtual ~IRenderingStrategy() = default;

        friend RenderingStrategyBase;
        friend PhysicsRenderingDecorator;

    protected:
        virtual const Graphics::Models::Matrix4x4f &getModelMatrix() const = 0;

        virtual void _updateModelMatrix(const Components::Graphics::Models::Matrix4x4f &parentMatrix, bool isPrsUpdated = false) = 0;

        virtual void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) = 0;
        virtual void _onDetachedFromParent() = 0;
    };
}

#endif // TENGINE_IRENDERINGSTRATEGY_H