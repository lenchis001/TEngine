#ifndef TENGINE_IPHYSICSSERVICE_H
#define TENGINE_IPHYSICSSERVICE_H

namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics
{
    class IPhysicsService
    {
    public:
        virtual ~IPhysicsService() = default;

        virtual void initialize() = 0;

        virtual void update(double time) = 0;
    };
}

#endif // TENGINE_IPHYSICSSERVICE_H