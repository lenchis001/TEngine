#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include <memory>
#include <vector>

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

        ~SkySphereRenderingStrategy();

        void setTexture(const std::string &texturePath);

        void setSphere(float radius, int sectorCount, int stackCount);

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    private:
        static std::vector<float> _generateHalfSphereVertices(float radius, int sectorCount, int stackCount);

        void _releaseBuffers();


        GLuint _textureId, _vao;

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _texturesService;
    };
} // namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies