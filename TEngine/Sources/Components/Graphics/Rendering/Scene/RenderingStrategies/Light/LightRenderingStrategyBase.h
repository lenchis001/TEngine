#include "ILightRenderingStrategy.h"

#include <memory>

#include "Components/Graphics/Rendering/Scene/Lights/ILightService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light
{
    class LightRenderingStrategyBase : public ILightRenderingStrategy
    {
    public:
        LightRenderingStrategyBase(std::shared_ptr<ILightService> lightService);

    private:
        std::shared_ptr<ILightService> _lightService;
    };
}