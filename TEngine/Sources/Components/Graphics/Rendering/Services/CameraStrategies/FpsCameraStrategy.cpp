#define _USE_MATH_DEFINES
#include "cmath"

#include "FpsCameraStrategy.h"

#include "iostream"

#include "algorithm"
#include "functional"

using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;

using namespace TEngine::Components::Events::Models;

FpsCameraStrategy::FpsCameraStrategy(
    std::shared_ptr<IEventService> eventService,
    float fov,
    float aspectRatio,
    float zNear,
    float zFar,
    const Vector3df &position)
    : CameraStrategyBase(fov, aspectRatio, zNear, zFar, position, Vector3df(0.0f, 0.0f, 0.0f)),
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
      _isBoostActivated(false)
{
    _eventService->registerHandler(std::bind(&FpsCameraStrategy::_onMouseMoved, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerHandler(KeyboardKeys::KEY_W, std::bind(&FpsCameraStrategy::_onKeyWPressed, this, std::placeholders::_1));
    _eventService->registerHandler(KeyboardKeys::KEY_S, std::bind(&FpsCameraStrategy::_onKeySPressed, this, std::placeholders::_1));
    _eventService->registerHandler(KeyboardKeys::KEY_A, std::bind(&FpsCameraStrategy::_onKeyAPressed, this, std::placeholders::_1));
    _eventService->registerHandler(KeyboardKeys::KEY_D, std::bind(&FpsCameraStrategy::_onKeyDPressed, this, std::placeholders::_1));
    _eventService->registerHandler(KeyboardKeys::KEY_Q, std::bind(&FpsCameraStrategy::_onKeyQPressed, this, std::placeholders::_1));
    _eventService->registerHandler(KeyboardKeys::KEY_E, std::bind(&FpsCameraStrategy::_onKeyEPressed, this, std::placeholders::_1));
    _eventService->registerHandler(KeyboardKeys::KEY_LEFT_SHIFT, std::bind(&FpsCameraStrategy::_onKeyShiftPressed, this, std::placeholders::_1));

    _recalculateState();

    _eventService->setCursorePosition(1024 / 2, 768 / 2);
}

FpsCameraStrategy::~FpsCameraStrategy()
{
    _eventService->unregisterHandler(std::bind(&FpsCameraStrategy::_onMouseMoved, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterHandler(KeyboardKeys::KEY_W, std::bind(&FpsCameraStrategy::_onKeyWPressed, this, std::placeholders::_1));
    _eventService->unregisterHandler(KeyboardKeys::KEY_S, std::bind(&FpsCameraStrategy::_onKeySPressed, this, std::placeholders::_1));
    _eventService->unregisterHandler(KeyboardKeys::KEY_A, std::bind(&FpsCameraStrategy::_onKeyAPressed, this, std::placeholders::_1));
    _eventService->unregisterHandler(KeyboardKeys::KEY_D, std::bind(&FpsCameraStrategy::_onKeyDPressed, this, std::placeholders::_1));
    _eventService->unregisterHandler(KeyboardKeys::KEY_Q, std::bind(&FpsCameraStrategy::_onKeyQPressed, this, std::placeholders::_1));
    _eventService->unregisterHandler(KeyboardKeys::KEY_E, std::bind(&FpsCameraStrategy::_onKeyEPressed, this, std::placeholders::_1));
    _eventService->unregisterHandler(KeyboardKeys::KEY_LEFT_SHIFT, std::bind(&FpsCameraStrategy::_onKeyShiftPressed, this, std::placeholders::_1));
}

void FpsCameraStrategy::render()
{
    _recalculateState();
    CameraStrategyBase::render();
}

bool FpsCameraStrategy::_onMouseMoved(float x, float y)
{
    auto xDelta = x - 1024 / 2;
    auto yDelta = y - 768 / 2;

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

    _eventService->setCursorePosition(1024 / 2, 768 / 2);

    _isRorated = true;

    return true;
}

bool FpsCameraStrategy::_onKeyWPressed(bool isPressed)
{
    _isMovingForward = isPressed;

    return true;
}

bool FpsCameraStrategy::_onKeySPressed(bool isPressed)
{
    _isMovingBackward = isPressed;

    return true;
}

bool FpsCameraStrategy::_onKeyAPressed(bool isPressed)
{
    _isMovingLeft = isPressed;

    return true;
}

bool FpsCameraStrategy::_onKeyDPressed(bool isPressed)
{
    _isMovingRight = isPressed;

    return true;
}

bool FpsCameraStrategy::_onKeyQPressed(bool isPressed)
{
    _isMovingUp = isPressed;

    return true;
}

bool FpsCameraStrategy::_onKeyEPressed(bool isPressed)
{
    _isMovingDown = isPressed;

    return true;
}

bool FpsCameraStrategy::_onKeyShiftPressed(bool isPressed)
{
    _isBoostActivated = isPressed;

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