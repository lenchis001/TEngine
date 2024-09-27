#ifndef TENGINE_PHYSICSSERVICE_H
#define TENGINE_PHYSICSSERVICE_H

#include "IPhysicsService.h"

#include "btBulletDynamicsCommon.h"

namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics
{
    class PhysicsService : public IPhysicsService
    {
    public:
        PhysicsService();
        ~PhysicsService() override;

        void initialize() override;

        void update(double time) override;

    private:
        btDiscreteDynamicsWorld *_dynamicsWorld;

        double _lastTime;
    };
}

#endif // TENGINE_PHYSICSSERVICE_H