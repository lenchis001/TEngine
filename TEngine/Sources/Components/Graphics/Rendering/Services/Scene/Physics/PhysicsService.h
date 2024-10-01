#ifndef TENGINE_PHYSICSSERVICE_H
#define TENGINE_PHYSICSSERVICE_H

#include "IPhysicsService.h"

#include <memory>
#include <unordered_map>

#include "btBulletDynamicsCommon.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics
{
    class PhysicsService : public IPhysicsService
    {
    public:
        PhysicsService();
        ~PhysicsService() override;

        void initialize() override;

        void update(double time) override;

        void addStaticBox(
            const Vector3df &size,
            std::shared_ptr<IRenderingStrategy> renderingStrategy) override;

        void addDynamicBox(
            const Vector3df &size,
            std::shared_ptr<IRenderingStrategy> renderingStrategy) override;

        void setPosition(
            const std::shared_ptr<IRenderingStrategy> renderingStrategy,
            const Vector3df &position) override;

    private:
        void _syncRenderingState();

        btDiscreteDynamicsWorld *_dynamicsWorld;

        double _lastTime;

        std::unordered_map<std::shared_ptr<IRenderingStrategy>, btRigidBody *> _objects;
    };
}

#endif // TENGINE_PHYSICSSERVICE_H