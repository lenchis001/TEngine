#include <memory>

#include "Components/Graphics/Rendering/Scene/Lights/ILightService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies
{
    class LightRenderingStrategyAware
    {
    public:
        LightRenderingStrategyAware(std::shared_ptr<ILightService> lightService);
    };
}lk;