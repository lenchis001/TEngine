#include "LightService.h"

#include "Components/Graphics/Rendering/Models/Lights/PointLight.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Lights;

LightService::LightService()
    : _pointLight(std::make_shared<PointLight>(Vector3df(0.0f, 10.0f, 0.0f), Vector3df(1.0f, 1.0f, 1.0f)))
{
}

bool asc = true;

void LightService::update()
{
    auto position = _pointLight->getPosition();

    if (position.getX() > 60.0f)
    {
        asc = false;
    }
    else if (position.getX() < 0.0f)
    {
        asc = true;
    }

    position.setX(position.getX() + (asc ? 0.5f : -0.5f));
    position.setZ(position.getZ() + (asc ? 0.5f : -0.5f));

    _pointLight->setPosition(position);
}

const std::shared_ptr<IPointLight> LightService::getPointLight() const
{
    return _pointLight;
}