#include "PointLight.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Lights;

PointLight::PointLight(const Vector3df &position, const Vector3df &diffuseColor)
    : _position(position), _diffuseColor(diffuseColor)
{
}

void PointLight::setPosition(const Vector3df &position)
{
    _position = position;
}

const Vector3df& PointLight::getPosition() const
{
    return _position;
}

const Vector3df& PointLight::getDiffuseColor() const
{
    return _diffuseColor;
}