#include <memory>
#include <vector>

#include <GLFW/glfw3.h>

#include "ISkySphereRenderingStrategy.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky
{
    class SkySphereRenderingStrategy : public RenderingStrategyBase, public ISkySphereRenderingStrategy
    {
    public:
        SkySphereRenderingStrategy(std::shared_ptr<IShadersService> shadersService,
                                   std::shared_ptr<IBuffersService> bufferCacheService,
                                   std::shared_ptr<ITexturesService> texturesService);

        ~SkySphereRenderingStrategy();

        void setTexture(
            const std::string &rightTexturePath,
            const std::string &leftTexturePath,
            const std::string &topTexturePath,
            const std::string &bottomTexturePath,
            const std::string &frontTexturePath,
            const std::string &backTexturePath);

        void setCube(float size);

        std::type_index getType() const override;

    protected:
        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    private:
        static std::vector<float> _generateCubeVertices(float size);

        void _releaseBuffers();
        void _prepareShader();

        GLuint _textureId, _vao, _matrixShaderId, _cubeSamplerShaderId, _shaderProgram;

        int _sectorCount;

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _texturesService;
    };
} // namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies