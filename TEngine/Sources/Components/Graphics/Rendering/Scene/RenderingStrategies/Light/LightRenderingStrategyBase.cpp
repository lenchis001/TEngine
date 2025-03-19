#include "LightRenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light;

LightRenderingStrategyBase::LightRenderingStrategyBase(std::shared_ptr<ILightService> lightService)
    : _lightService(lightService)
{
}

void LightRenderingStrategyBase::updatePointLights(const std::vector<std::shared_ptr<IPointLight>> &&pointLights)
{
    _pointLights = pointLights;
}

Vector3df LightRenderingStrategyBase::_determineSize(const std::vector<float> &vertices)
{
    Vector3df min(0, 0, 0);
    Vector3df max(0, 0, 0);

    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        min.setX(std::min(min.getX(), vertices[i]));
        min.setY(std::min(min.getY(), vertices[i + 1]));
        min.setZ(std::min(min.getZ(), vertices[i + 2]));

        max.setX(std::max(max.getX(), vertices[i]));
        max.setY(std::max(max.getY(), vertices[i + 1]));
        max.setZ(std::max(max.getZ(), vertices[i + 2]));
    }

    return Vector3df(
        std::abs(min.getX()) + std::abs(max.getX()),
        std::abs(min.getY()) + std::abs(max.getY()),
        std::abs(min.getZ()) + std::abs(max.getZ()));
}