#ifndef TENGINE_PHYSICSRENDERINGDECORATOR_H
#define TENGINE_PHYSICSRENDERINGDECORATOR_H

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

#include <memory>

#include "Components/Graphics/Rendering/Scene/Physics/IPhysicsService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies
{
    class PhysicsRenderingDecorator : public std::enable_shared_from_this<PhysicsRenderingDecorator>, public IRenderingStrategy
    {
    public:
        PhysicsRenderingDecorator(std::shared_ptr<IPhysicsService> physicsService, std::shared_ptr<IRenderingStrategy> strategy, PhysicsFlags physicsFlags);

        ~PhysicsRenderingDecorator() override = default;

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        void setPosition(const Vector3df &position) override;

        void setRotation(const Vector3df &rotation) override;

        void setScale(const Vector3df &scale) override;

        const Vector3df &getPosition() const override;

        const Vector3df &getRotation() const override;

        const Vector3df &getScale() const override;

        void setAbsolutePosition(const Vector3df &position) override;

        void setAbsoluteRotation(const Vector3df &rotation) override;

        Vector3df getAbsolutePosition() const override;

        Vector3df getAbsoluteRotation() const override;

        Vector3df getAbsoluteScale() const override;

        const std::vector<std::shared_ptr<IRenderingStrategy>> &getChildren() const override;

        void addChild(std::shared_ptr<IRenderingStrategy> child) override;

        void removeChild(std::shared_ptr<IRenderingStrategy> child) override;

        void removeAllChildren() override;

        std::vector<float> getVertices() const override;

        std::type_index getType() const override;

        PhysicsFlags getPhysicsFlags() const;

        std::shared_ptr<IRenderingStrategy> getInternalStrategy();

    protected:
        const Matrix4x4f &getModelMatrix() const override;

        void _updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated = false) override;

        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;
        void _onDetachedFromParent() override;

    private:
        std::shared_ptr<IPhysicsService> _physicsService;
        std::shared_ptr<IRenderingStrategy> _strategy;

        PhysicsFlags _physicsFlags;
    };
}

#endif // TENGINE_PHYSICSRENDERINGDECORATOR_H