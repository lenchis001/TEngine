#ifndef TENGINE_CUBE_RENDERING_STRATEGY_H
#define TENGINE_CUBE_RENDERING_STRATEGY_H

#include <memory>

#include "GLFW/glfw3.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"
#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/ImageLoading/Models/Image.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives
{
    class CubeRenderingStrategy : public RenderingStrategyBase
    {
    public:
        CubeRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::string texturePath);
        ~CubeRenderingStrategy() override;

        std::vector<float> getVertices() const override;

        std::type_index getType() const override;

        const std::string &getTexturePath() const;

    protected:
        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    private:
        void _prepareVertexVbo();
        void _prepareTexture();
        void _prepareUvVbo();
        void _prepareVao();
        void _prepareShader();

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _texturesService;

        GLuint _shaderProgram, _matrixShaderId, _textureId, _textureSamplerShaderId, _vao;

        std::string _texturePath;

        static std::vector<float> _vertices;
    };
}

#endif // TENGINE_CUBE_RENDERING_STRATEGY_H