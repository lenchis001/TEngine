#ifndef TENGINE_ICAMERASTRATEGY_H
#define TENGINE_ICAMERASTRATEGY_H

#include "Components/Graphics/Models/Vector2d.h"
#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Models/Matrix4x4.h"

#include "Tracking/ICameraTrackingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies
{

    class ICameraStrategy
    {
    public:
        virtual const TEngine::Components::Graphics::Models::Vector3df &getPosition() const = 0;
        virtual void setPosition(const TEngine::Components::Graphics::Models::Vector3df& value) = 0;

        virtual const TEngine::Components::Graphics::Models::Vector3df &getTarget() const = 0;
        virtual void setTarget(const TEngine::Components::Graphics::Models::Vector3df& value) = 0;

        virtual void setTargetAndPosition(const TEngine::Components::Graphics::Models::Vector3df& target, const TEngine::Components::Graphics::Models::Vector3df& position) = 0;

        virtual void render(double time) = 0;

        virtual const TEngine::Components::Graphics::Models::Matrix4x4f &getVpMatrix() const = 0;

        virtual const TEngine::Components::Graphics::Models::Matrix4x4f &getViewMatrix() const = 0;

        virtual void setWindowSize(const TEngine::Components::Graphics::Models::Vector2di& value) = 0;

        virtual void addTrackingStrategy(std::shared_ptr<Tracking::ICameraTrackingStrategy> trackingStrategy) = 0;

        virtual ~ICameraStrategy() = default;
    };

}

#endif // TENGINE_ICAMERASTRATEGY_H