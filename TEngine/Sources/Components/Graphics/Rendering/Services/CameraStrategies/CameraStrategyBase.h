#ifndef TENGINE_CAMERASTRATEGYBASE_H
#define TENGINE_CAMERASTRATEGYBASE_H

#include "ICameraStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies
{

    class CameraStrategyBase : public ICameraStrategy
    {
    public:
        CameraStrategyBase(
            float fov,
            float aspectRatio,
            float zNear,
            float zFar,
            const TEngine::Components::Graphics::Models::Vector3df &position,
            const TEngine::Components::Graphics::Models::Vector3df &target);

        const TEngine::Components::Graphics::Models::Vector3df &getPosition() const override;
        void setPosition(const TEngine::Components::Graphics::Models::Vector3df &value) override;

        const TEngine::Components::Graphics::Models::Vector3df &getTarget() const override;
        void setTarget(const TEngine::Components::Graphics::Models::Vector3df &value) override;

        void render() override;

        const TEngine::Components::Graphics::Models::Matrix4x4f &getVpMatrix() const override;

    protected:
        void _recalculateProjection();
        void _recalculateView();
        void _recalculateVp();

        float _fov, _aspectRatio, _zNear, _zFar;

        TEngine::Components::Graphics::Models::Vector3df _position, _target;
        TEngine::Components::Graphics::Models::Matrix4x4f _projectionMatrix, _viewMatrix, _vpMatrix;
    };

}

#endif // TENGINE_CAMERASTRATEGYBASE_H