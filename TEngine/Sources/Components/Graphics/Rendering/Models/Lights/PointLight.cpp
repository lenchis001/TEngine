#include "PointLight.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Lights;

PointLight::PointLight(const Vector3df &position, const Vector3df &diffuseColor, float radius, LightUpdateRequiredCallback lightUpdateRequiredCallback)
	: _position(position),
    _diffuseColor(diffuseColor),
    _radius(radius),
    _lightUpdateRequiredCallback(lightUpdateRequiredCallback)
{
}

void PointLight::setPosition(const Vector3df &position)
{
    _position = position;

    _lightUpdateRequiredCallback();
}

const Vector3df& PointLight::getPosition() const
{
    return _position;
}

const Vector3df& PointLight::getDiffuseColor() const
{
    return _diffuseColor;
}

float PointLight::getRadius() const
{
    return _radius;
}

void PointLight::setRadius(float radius)
{
	_radius = radius;

    _lightUpdateRequiredCallback();
}
