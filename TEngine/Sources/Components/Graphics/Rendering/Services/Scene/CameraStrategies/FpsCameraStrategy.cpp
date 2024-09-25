#define _USE_MATH_DEFINES
#include "cmath"

#include "FpsCameraStrategy.h"

#include <algorithm>
#include <functional>

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies;

using namespace TEngine::Components::Events::Models;

FpsCameraStrategy::FpsCameraStrategy(
    std::shared_ptr<IEventService> eventService,
    float fov,
    const Vector2di &windowSize,
    float zNear,
    float zFar,
    const Vector3df &position)
    : CameraStrategyBase(fov, windowSize, zNear, zFar, position, Vector3df(0.0f, 0.0f, 0.0f)),
      _eventService(eventService),
      _speed(0.1f),
      _phi(0.0f),
      _theta(M_PI * 3 / 4),
      _position(position),
      _target(Vector3df(0.0f, 0.0f, 0.0f)),
      _radius(1.0f),
      _isMovingForward(false),
      _isMovingBackward(false),
      _isMovingLeft(false),
      _isMovingRight(false),
      _isMovingUp(false),
      _isMovingDown(false),
      _isBoostActivated(false),
      _windowCenter(windowSize / 2)
{
    _eventService->registerCursorMoveHandler(std::bind(&FpsCameraStrategy::_onMouseMoved, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerKeyHandler(std::bind(&FpsCameraStrategy::_onKeyPressed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    setWindowSize(Vector2di(1280, 720));
    _eventService->setCursorVisibility(false);
}

FpsCameraStrategy::~FpsCameraStrategy()
{
    _eventService->unregisterCursorMoveHandler(std::bind(&FpsCameraStrategy::_onMouseMoved, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterKeyHandler(std::bind(&FpsCameraStrategy::_onKeyPressed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void FpsCameraStrategy::render()
{
    _recalculateState();
    CameraStrategyBase::render();
}

void FpsCameraStrategy::setWindowSize(const Vector2di &value)
{
    CameraStrategyBase::setWindowSize(value);

    _windowCenter = value / 2;

    _eventService->setCursorePosition(_windowCenter);
}

bool FpsCameraStrategy::_onMouseMoved(float x, float y)
{
    auto xDelta = x - _windowCenter.getX();
    auto yDelta = y - _windowCenter.getY();

    _phi += xDelta * 0.001f;
    if (_phi > 2 * M_PI)
    {
        _phi -= 2 * M_PI;
    }
    else if (_phi < 0)
    {
        _phi += 2 * M_PI;
    }

    _theta += yDelta * 0.001f;
    _theta = std::clamp(_theta, 0.0f, static_cast<float>(M_PI));

    _eventService->setCursorePosition(_windowCenter);

    _isRorated = true;

    return true;
}

#define GLFW_PRESS 1

bool FpsCameraStrategy::_onKeyPressed(int key, int scancode, int action, int mods)
{
    if (key == (int)KeyboardKeys::KEY_W)
    {
        _isMovingForward = action == GLFW_PRESS;
    } else if (key == (int)KeyboardKeys::KEY_S)
    {
        _isMovingBackward = action == GLFW_PRESS;
    } else if (key == (int)KeyboardKeys::KEY_A)
    {
        _isMovingLeft = action == GLFW_PRESS;
    } else if (key == (int)KeyboardKeys::KEY_D)
    {
        _isMovingRight = action == GLFW_PRESS;
    } else if (key == (int)KeyboardKeys::KEY_Q)
    {
        _isMovingUp = action == GLFW_PRESS;
    } else if (key == (int)KeyboardKeys::KEY_E)
    {
        _isMovingDown = action == GLFW_PRESS;
    } else if (key == (int)KeyboardKeys::KEY_LEFT_SHIFT)
    {
        _isBoostActivated = action == GLFW_PRESS;
    }

    return true;
}

void FpsCameraStrategy::_recalculateState()
{
    if (_isMovingForward)
    {
        auto direction = _position - _target;

        _position = _position - direction.getNormalized() * (_speed * (_isBoostActivated ? 3.0f : 1.0f));
    }

    if (_isMovingBackward)
    {
        auto direction = _position - _target;

        _position = _position + direction.getNormalized() * (_speed * (_isBoostActivated ? 3.0f : 1.0f));
    }

    if (_isMovingLeft)
    {
        auto direction = _position - _target;
        auto right = direction.cross(Vector3df(0.0f, 1.0f, 0.0f));

        _position = _position + right.getNormalized() * (_speed * (_isBoostActivated ? 3.0f : 1.0f));
    }

    if (_isMovingRight)
    {
        auto direction = _position - _target;
        auto right = direction.cross(Vector3df(0.0f, 1.0f, 0.0f));

        _position = _position - right.getNormalized() * (_speed * (_isBoostActivated ? 3.0f : 1.0f));
    }

    if (_isMovingUp)
    {
        _position = _position + Vector3df(0.0f, _speed * (_isBoostActivated ? 3.0f : 1.0f), 0.0f);
    }

    if (_isMovingDown)
    {
        _position = _position - Vector3df(0.0f, _speed * (_isBoostActivated ? 3.0f : 1.0f), 0.0f);
    }

    if (_isMovingForward || _isMovingBackward || _isMovingLeft || _isMovingRight || _isMovingUp || _isMovingDown || _isRorated)
    {
        _recalculateTarget();

        setTargetAndPosition(_target, _position);
    }
}

void FpsCameraStrategy::_recalculateTarget()
{
    _target = _position + Vector3df(
                              _radius * sin(_theta) * cos(_phi),
                              _radius * cos(_theta),
                              _radius * sin(_theta) * sin(_phi));
}