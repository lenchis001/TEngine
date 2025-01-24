#ifndef TENGINE_PHYSICSRENDERINGMIXIN_H
#define TENGINE_PHYSICSRENDERINGMIXIN_H

#include <memory>

#include "IPhysicsRenderingAware.h"

#include "Components/Graphics/Rendering/Scene/Physics/IPhysicsService.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingMixins
{
    // todo: rename PhysicsRenderingStrategyBase?
    class PhysicsRenderingStrategyBase : public RenderingStrategyBase, public virtual IPhysicsRenderingAware
    {
    public:
        PhysicsRenderingStrategyBase(std::shared_ptr<IPhysicsService> physicsService, OnDeleteCallback onDeleteCallback);

        void setPosition(const Vector3df &position) override;

        void setRotation(const Vector3df &rotation) override;

        void setScale(const Vector3df &scale) override;

        void setPhysicsFlags(PhysicsFlags physicsFlags) override;

        PhysicsFlags getPhysicsFlags() const override;

    protected:
        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;
        void _onDetachedFromParent() override;

        bool _isPhysicsEnabled() const;

        std::vector<float> getVertices() const final;

        void setDirectAbsolutePosition(const Vector3df &position) final;

        void setDirectAbsoluteRotation(const Vector3df &rotation) final;

        virtual std::vector<float> _getVertices() const = 0;

    private:
        void _attachToPhysics();

        std::shared_ptr<IPhysicsRenderingAware> _getSharedPhysicsRenderingAware();

        std::shared_ptr<IPhysicsService> _physicsService;

        PhysicsFlags _physicsFlags;

        bool _isAttachedToParent;
    };
}

#endif // TENGINE_PHYSICSRENDERINGMIXIN_H