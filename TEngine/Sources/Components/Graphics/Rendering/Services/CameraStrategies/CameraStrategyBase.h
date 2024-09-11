#ifndef TENGINE_CAMERASTRATEGYBASE_H
#define TENGINE_CAMERASTRATEGYBASE_H

#include "ICameraStrategy.h"

using namespace TEngine::Components::Graphics::Models;

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
            const Vector3df &position,
            const Vector3df &target);

        const Vector3df &getPosition() const override;
        void setPosition(const Vector3df &value) override;

        const Vector3df &getTarget() const override;
        void setTarget(const Vector3df &value) override;

        void setTargetAndPosition(const Vector3df &target, const Vector3df &position) override;

        void render() override;

        inline const Matrix4x4f &getVpMatrix() const override {
            return _vpMatrix;
        }

        inline const Matrix4x4f &getViewMatrix() const override {
            return _viewMatrix;
        }

        ~CameraStrategyBase() override = default;

        void setAspectRatio(float value) override;

    protected:
        void _recalculateProjection();
        void _recalculateView();
        void _recalculateVp();

        float _fov, _aspectRatio, _zNear, _zFar;

        Vector3df _position, _target;
        Matrix4x4f _projectionMatrix, _viewMatrix, _vpMatrix;
    };

}

#endif // TENGINE_CAMERASTRATEGYBASE_H