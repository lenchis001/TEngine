#include "ILightRenderingStrategy.h"

#include <memory>
#include <vector>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/Lights/ILightService.h"

#include "GLFW/glfw3.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Lights::Shader;
using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light
{
    class LightRenderingStrategyBase : public virtual ILightRenderingStrategy
    {
    public:
        LightRenderingStrategyBase(std::shared_ptr<ILightService> lightService);

        void updatePointLights(const std::vector<ShaderPointLight>&& pointLights) override;

    protected:
        GLuint getPointLightsBuffer() const;
        GLuint getPointLightsAmount() const;

        static Vector3df _determineSize(const std::vector<float> &vertices);
    private:
        GLuint _pointLightsBuffer;
        GLuint _pointLightsAmount;
        std::shared_ptr<ILightService> _lightService;
    };
}