#include "IPhysicsService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::Physics
{
    class EmptyPhysicsService : public IPhysicsService
    {
    public:
        void initialize() override;

        void update(double time) override;

        void addBox(
            std::shared_ptr<IRenderingStrategy> renderingStrategy,
            float mass) override;

        void removeBox(
            std::shared_ptr<IRenderingStrategy> renderingStrategy) override;

        void setPosition(
            const std::shared_ptr<IRenderingStrategy> renderingStrategy,
            const Vector3df &position) override;

        void setRotation(
            const std::shared_ptr<IRenderingStrategy> renderingStrategy,
            const Vector3df &rotation) override;
    };
}