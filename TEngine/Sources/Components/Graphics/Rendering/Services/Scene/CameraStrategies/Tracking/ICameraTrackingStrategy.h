#ifndef TENGINE_ICAMERATRACKINGSTRATEGY_H
#define TENGINE_ICAMERATRACKINGSTRATEGY_H

#include "Components/Graphics/Models/Vector3d.h"

namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies::Tracking
{
    class ICameraTrackingStrategy
    {
    public:
        virtual ~ICameraTrackingStrategy() = default;

        virtual void onPositionUpdated(const  Graphics::Models::Vector3df &position) = 0;

        virtual void onTargetUpdated(const Graphics::Models::Vector3df &target) = 0;
    };
}

#endif // TENGINE_ICAMERATRACKINGSTRATEGY_H