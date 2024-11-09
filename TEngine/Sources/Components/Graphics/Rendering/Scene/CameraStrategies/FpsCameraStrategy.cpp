#define _USE_MATH_DEFINES
#include <cmath>

#include "FpsCameraStrategy.h"

#include <algorithm>
#include <functional>

#include "Components/Events/Models/KeyStates.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies;

using namespace TEngine::Components::Events::Models;

#define BOOSTED_SPEED(normalSpeed) (normalSpeed * 2.f)

FpsCameraStrategy::FpsCameraStrategy(
    std::shared_ptr<IEventService> eventService,
    float fov,
    const Vector2di &windowSize,
    float zNear,
    float zFar,
    const Vector3df &position)
    : CameraStrategyBase(fov, windowSize, zNear, zFar, position, Vector3df(0.0f, 0.0f, 0.0f)),
      _eventService(eventService),
      _speed(3.f),
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
      _windowCenter(windowSize / 2),
      _lastTime(0.0)
{
    _eventService->registerCursorMoveHandler(std::bind(&FpsCameraStrategy::_onMouseMoved, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->registerKeyHandler(std::bind(&FpsCameraStrategy::_onKeyPressed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

    _eventService->setCursorVisibility(false);
}

FpsCameraStrategy::~FpsCameraStrategy()
{
    _eventService->unregisterCursorMoveHandler(std::bind(&FpsCameraStrategy::_onMouseMoved, this, std::placeholders::_1, std::placeholders::_2));
    _eventService->unregisterKeyHandler(std::bind(&FpsCameraStrategy::_onKeyPressed, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
}

void FpsCameraStrategy::render(double time)
{
    _recalculateState(time);
    CameraStrategyBase::render(time);
}

void FpsCameraStrategy::setWindowSize(const Vector2di &value)
{
    CameraStrategyBase::setWindowSize(value);

    _windowCenter = value / 2;

    _eventService->setCursorePosition(_windowCenter);
}

bool FpsCameraStrategy::_onMouseMoved(int x, int y)
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

bool FpsCameraStrategy::_onKeyPressed(KeyboardKeys key, int scancode, KeyStates action, int mods)
{
    if (key == KeyboardKeys::KEY_W)
    {
        _isMovingForward = action != KeyStates::RELEASE;
    }
    else if (key == KeyboardKeys::KEY_S)
    {
        _isMovingBackward = action != KeyStates::RELEASE;
    }
    else if (key == KeyboardKeys::KEY_A)
    {
        _isMovingLeft = action != KeyStates::RELEASE;
    }
    else if (key == KeyboardKeys::KEY_D)
    {
        _isMovingRight = action != KeyStates::RELEASE;
    }
    else if (key == KeyboardKeys::KEY_Q)
    {
        _isMovingUp = action != KeyStates::RELEASE;
    }
    else if (key == KeyboardKeys::KEY_E)
    {
        _isMovingDown = action != KeyStates::RELEASE;
    }
    else if (key == KeyboardKeys::KEY_LEFT_SHIFT)
    {
        _isBoostActivated = action != KeyStates::RELEASE;
    }

    return true;
}

void FpsCameraStrategy::_recalculateState(double time)
{
    if(_lastTime == 0.0)
    {
        _lastTime = time;
    }

    auto deltaTime = time - _lastTime;
    _lastTime = time;
    auto speed = _speed * (_isBoostActivated ? BOOSTED_SPEED(deltaTime) : deltaTime);

    if (_isMovingForward)
    {
        auto direction = _position - _target;

        _position = _position - direction.getNormalized() * speed;
    }

    if (_isMovingBackward)
    {
        auto direction = _position - _target;

        _position = _position + direction.getNormalized() * speed;
    }

    if (_isMovingLeft)
    {
        auto direction = _position - _target;
        auto right = direction.cross(Vector3df(0.0f, 1.0f, 0.0f));

        _position = _position + right.getNormalized() * speed;
    }

    if (_isMovingRight)
    {
        auto direction = _position - _target;
        auto right = direction.cross(Vector3df(0.0f, 1.0f, 0.0f));

        _position = _position - right.getNormalized() * speed;
    }

    if (_isMovingUp)
    {
        _position = _position + Vector3df(0.0f, speed, 0.0f);
    }

    if (_isMovingDown)
    {
        _position = _position - Vector3df(0.0f, speed, 0.0f);
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