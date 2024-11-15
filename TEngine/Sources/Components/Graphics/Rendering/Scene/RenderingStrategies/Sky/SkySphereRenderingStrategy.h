#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include <memory>

#include <GLFW/glfw3.h>

#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky
{
    class SkySphereRenderingStrategy : public RenderingStrategyBase
    {
    public:
        SkySphereRenderingStrategy(std::shared_ptr<IShadersService> shadersService,
                                   std::shared_ptr<IBuffersService> bufferCacheService,
                                   std::shared_ptr<ITexturesService> texturesService);

        void setTexture(const std::string &texturePath);

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    private:
        GLuint _textureId;

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _texturesService;
    };
} // namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies