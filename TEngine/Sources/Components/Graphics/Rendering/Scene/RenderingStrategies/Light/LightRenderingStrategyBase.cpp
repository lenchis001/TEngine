#include "LightRenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light;

LightRenderingStrategyBase::LightRenderingStrategyBase(std::shared_ptr<ILightService> lightService)
    : _lightService(lightService)
{
}