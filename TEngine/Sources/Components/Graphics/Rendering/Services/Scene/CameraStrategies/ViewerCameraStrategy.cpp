#include "ViewerCameraStrategy.h"

#include <functional>

#include "Components/Events/Models/KeyStates.h"
#include "Components/Events/Models/MouseButtons.h"

using namespace TEngine::Components::Events::Models;

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies;

ViewerCameraStrategy::ViewerCameraStrategy(
    std::shared_ptr<IEventService> eventService,
    float fov,
    const Vector2di &windowSize,
    float zNear,
    float zFar,
    const Vector3df &position) : FpsCameraStrategy(eventService,
                                                   fov,
                                                   windowSize,
                                                   zNear,
                                                   zFar,
                                                   position),
                                 _previousX(-1.f),
                                 _previousY(-1.f),
                                 _isRotationAllowed(false)
{
    _eventService->setCursorVisibility(true);

    _eventService->registerMouseButtonHandler(std::bind(&ViewerCameraStrategy::_onMouseButton, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

ViewerCameraStrategy::~ViewerCameraStrategy() {
    _eventService->unregisterMouseButtonHandler(std::bind(&ViewerCameraStrategy::_onMouseButton, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
}

bool ViewerCameraStrategy::_onMouseMoved(float x, float y)
{
    if (_previousX > 0 && _isRotationAllowed)
    {
        auto xDelta = _previousX - x;
        auto yDelta = _previousY - y;

        _phi += xDelta * 0.002f;
        if (_phi > 2 * M_PI)
        {
            _phi -= 2 * M_PI;
        }
        else if (_phi < 0)
        {
            _phi += 2 * M_PI;
        }

        _theta += yDelta * 0.002f;
        _theta = std::clamp(_theta, 0.0f, static_cast<float>(M_PI));

        _isRorated = true;
    }

    _previousX = x;
    _previousY = y;

    return true;
}

bool ViewerCameraStrategy::_onMouseButton(int button, int action, int mods)
{
    if (button == (int)MouseButtons::BUTTON_LEFT)
    {
        _isRotationAllowed = action == (int)KeyStates::PRESS;
    }

    return true;
}