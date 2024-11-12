#ifndef TENGINE_VIEWER_CAMERA_STRATEGY_H
#define TENGINE_VIEWER_CAMERA_STRATEGY_H

#include "FpsCameraStrategy.h"

using namespace TEngine::Components::Events::Models;

namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies
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

        void setWindowSize(const Vector2di &value) override;

    protected:
        bool _onMouseMoved(int x, int y) override;

    private:
        bool _onMouseButton(MouseButtons button, KeyStates action, int mods);

        float _previousX, _previousY;
        bool _isRotationAllowed;
    };
}

#endif // TENGINE_VIEWER_CAMERA_STRATEGY_H