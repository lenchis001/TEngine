#ifndef TENGINE_VIEWER_CAMERA_STRATEGY_H
#define TENGINE_VIEWER_CAMERA_STRATEGY_H

#include "FpsCameraStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies
{
    class ViewerCameraStrategy : public FpsCameraStrategy
    {
    public:
        ViewerCameraStrategy(std::shared_ptr<IEventService> eventService,
                             float fov,
                             const Vector2di &windowSize,
                             float zNear,
                             float zFar,
                             const Vector3df &position);
        ~ViewerCameraStrategy();

    protected:
        bool _onMouseMoved(float x, float y) override;

    private:
        bool _onMouseButton(int button, int action, int mods);

        float _previousX, _previousY;
        bool _isRotationAllowed;
    };
}

#endif // TENGINE_VIEWER_CAMERA_STRATEGY_H