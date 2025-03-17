#include "IPhysicsService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Physics;

namespace TEngine::Components::Graphics::Rendering::Scene::Physics
{
    class EmptyPhysicsService : public IPhysicsService
    {
    public:
        void initialize() override;

        void update(double time) override;

        bool isAttached(
            std::shared_ptr<IPhysicsRenderingAware> renderingStrategy) override;

        void addBox(
            std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
            float mass) override;

        void removeBox(
            std::shared_ptr<IPhysicsRenderingAware> renderingStrategy) override;

        void setPosition(
            const std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
            const Vector3df &position) override;

        void setRotation(
            const std::shared_ptr<IPhysicsRenderingAware> renderingStrategy,
            const Vector3df &rotation) override;
    };
}