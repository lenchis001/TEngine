#include "CameraStrategyBase.h"

#define _USE_MATH_DEFINES
#include "math.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;

CameraStrategyBase::CameraStrategyBase(
    float fov, float aspectRatio, float zNear, float zFar, const Models::Vector3df &position, const Models::Vector3df &target) : _fov(fov),
                                                                                                                                 _aspectRatio(aspectRatio),
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
}

const Vector3df &CameraStrategyBase::getTarget() const
{
    return _target;
}

void CameraStrategyBase::setTarget(const Vector3df &value)
{
    _target = value;
}

void CameraStrategyBase::render()
{
}

const Matrix4x4f &CameraStrategyBase::getVpMatrix() const
{
    return _vpMatrix;
}

void CameraStrategyBase::_recalculateProjection()
{
    float tanHalfFov = tan(_fov / 2.f);
    float nearmfar = _zNear - _zFar;

    _projectionMatrix = Matrix4x4f(
        (1.f / (_aspectRatio * tanHalfFov)), .0f, .0f, .0f,
        .0f, (1.f / tanHalfFov), .0f, .0f,
        .0f, .0f, (_zFar + _zNear) / nearmfar, -1.f,
        .0f, .0f, 2.f * _zFar * _zNear / nearmfar, 0.f);
}

void CameraStrategyBase::_recalculateView()
{
    Vector3df dir = (_target - _position).getNormalized();

    Vector3df up(0.f, 1.f, 0.f);

    Vector3df zAxis = dir.getNegative();
    Vector3df xAxis = up.cross(zAxis);
    Vector3df yAxis = zAxis.cross(xAxis);

    // Create the view matrix
    _viewMatrix = Matrix4x4f(
        xAxis.getX(), yAxis.getX(), zAxis.getX(), _position.getX(),
        xAxis.getY(), yAxis.getY(), zAxis.getY(), _position.getY(),
        xAxis.getZ(), yAxis.getZ(), zAxis.getZ(), _position.getZ(),
        0.0f, 0.0f, 0.0f, 1.0f);




        // 		tvec3<T, P> const f(normalize(center - eye));
		// tvec3<T, P> const s(normalize(cross(f, up)));
		// tvec3<T, P> const u(cross(s, f));

		// tmat4x4<T, P> Result(1);
		// Result[0][0] = s.x;
		// Result[1][0] = s.y;
		// Result[2][0] = s.z;
		// Result[0][1] = u.x;
		// Result[1][1] = u.y;
		// Result[2][1] = u.z;
		// Result[0][2] =-f.x;
		// Result[1][2] =-f.y;
		// Result[2][2] =-f.z;
		// Result[3][0] =-dot(s, eye);
		// Result[3][1] =-dot(u, eye);
		// Result[3][2] = dot(f, eye);
}

void CameraStrategyBase::_recalculateVp()
{
    //_vpMatrix = _projectionMatrix * _viewMatrix;
}