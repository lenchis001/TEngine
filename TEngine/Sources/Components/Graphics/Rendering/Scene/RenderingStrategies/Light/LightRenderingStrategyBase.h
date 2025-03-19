#include "ILightRenderingStrategy.h"

#include <memory>
#include <vector>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/Lights/ILightService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Lights;
using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light
{
    class LightRenderingStrategyBase : public virtual ILightRenderingStrategy
    {
    public:
        LightRenderingStrategyBase(std::shared_ptr<ILightService> lightService);

        void updatePointLights(const std::vector<std::shared_ptr<IPointLight>>&& pointLights) override;

    protected:
        const std::vector<std::shared_ptr<IPointLight>> &getPointLights() const;

        static Vector3df _determineSize(const std::vector<float> &vertices);
    private:
        std::shared_ptr<ILightService> _lightService;
        std::vector<std::shared_ptr<IPointLight>> _pointLights;
    };
}