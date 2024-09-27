#include "CameraStrategyBase.h"

#define _USE_MATH_DEFINES
#include "math.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::CameraStrategies;

CameraStrategyBase::CameraStrategyBase(
    float fov,
    const Vector2di& windowSize,
    float zNear,
    float zFar,
    const Models::Vector3df &position,
    const Models::Vector3df &target)
    : _fov(fov),
      _aspectRatio(static_cast<float>(windowSize.getX()) / static_cast<float>(windowSize.getY())),
      _zNear(zNear),
      _zFar(zFar),
      _position(position),
      _target(target)
{
    _recalculateProjection();
    _recalculateView();
    _recalculateVp();
}

const Vector3df &CameraStrategyBase::getPosition() const
{
    return _position;
}

void CameraStrategyBase::setPosition(const Vector3df &value)
{
    _position = value;

    for (auto &trackingStrategy : _trackingStrategies)
    {
        trackingStrategy->onPositionUpdated(value);
    }

    _recalculateView();
    _recalculateVp();
}

const Vector3df &CameraStrategyBase::getTarget() const
{
    return _target;
}

void CameraStrategyBase::setTarget(const Vector3df &value)
{
    _target = value;

    for (auto &trackingStrategy : _trackingStrategies)
    {
        trackingStrategy->onTargetUpdated(value);
    }

    _recalculateView();
    _recalculateVp();
}

void CameraStrategyBase::setTargetAndPosition(const Vector3df &target, const Vector3df &position)
{
    _target = target;
    _position = position;

    for (auto &trackingStrategy : _trackingStrategies)
    {
        trackingStrategy->onPositionUpdated(position);
        trackingStrategy->onTargetUpdated(target);
    }

    _recalculateView();
    _recalculateVp();
}

void CameraStrategyBase::render(double time)
{
    // do nothing
}

void CameraStrategyBase::setWindowSize(const Vector2di &value)
{
    _aspectRatio = static_cast<float>(value.getX()) / static_cast<float>(value.getY());
    _recalculateProjection();
    _recalculateVp();
}

void CameraStrategyBase::addTrackingStrategy(std::shared_ptr<ICameraTrackingStrategy> trackingStrategy)
{
    _trackingStrategies.push_back(trackingStrategy);
}

void CameraStrategyBase::_recalculateProjection()
{
    float tanHalfFov = tan(_fov / 2.f);
    float nearmfar = _zFar - _zNear;

    _projectionMatrix = Matrix4x4f(
        (1.f / (_aspectRatio * tanHalfFov)), .0f, .0f, .0f,
        .0f, (1.f / tanHalfFov), .0f, .0f,
        .0f, .0f, -(_zFar + _zNear) / nearmfar, -(2.f * _zFar * _zNear) / nearmfar,
        .0f, .0f, -1.f, 0.f);
}

void CameraStrategyBase::_recalculateView()
{
    Vector3df up(0.f, 1.f, 0.f);

    auto f = (_target - _position).getNormalized();
    auto s = f.cross(up).getNormalized();
    auto u = s.cross(f);

    auto negativeF = f.getNegative();

    auto sPositionDot = -s.dot(_position);
    auto uPositionDot = -u.dot(_position);
    auto fPositionDot = f.dot(_position);

    // Create the view matrix
    _viewMatrix = Matrix4x4f(
        s.getX(), s.getY(), s.getZ(), sPositionDot,
        u.getX(), u.getY(), u.getZ(), uPositionDot,
        negativeF.getX(), negativeF.getY(), negativeF.getZ(), fPositionDot,
        0, 0, 0, 1.f);
}

void CameraStrategyBase::_recalculateVp()
{
    _vpMatrix = _projectionMatrix * _viewMatrix;
}