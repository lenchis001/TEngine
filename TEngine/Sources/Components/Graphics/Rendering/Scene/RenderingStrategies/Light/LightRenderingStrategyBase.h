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

        void updatePointLights(const std::vector<std::shared_ptr<Graphics::Rendering::Scene::Models::Lights::IPointLight>>& pointLights) override;

    private:
        std::shared_ptr<ILightService> _lightService;
    };
}