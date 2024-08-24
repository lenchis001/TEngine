#ifndef TENGINE_CUBE_RENDERING_STRATEGY_H
#define TENGINE_CUBE_RENDERING_STRATEGY_H

#include "memory"

#include "GLFW/glfw3.h"

#include "Components/Graphics/Rendering/Services/RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IRenderableObject.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"
#include "Components/Graphics/ImageLoading/Models/Image.h"
#include "Components/Graphics/Rendering/Services/Buffers/IBuffersService.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::ImageLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Buffers;

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives
{
    class CubeRenderingStrategy : public IRenderingStrategy
    {
    public:
        CubeRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<IRenderableObject> cube,
            std::shared_ptr<Image> image);
        ~CubeRenderingStrategy() override;

        void render(const Matrix4x4f &vpMatrix) override;

    private:
        void _prepareVertexVbo();
        void _prepareTexture(std::shared_ptr<Image> image);
        void _prepareUvVbo();
        void _prepareVao();
        void _prepareShader();

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;

        std::shared_ptr<IRenderableObject> _cube;

        GLuint _shaderProgram, _matrixShaderId, _textureId, _textureSamplerShaderId, _vao;

        Matrix4x4f _vpMatrix, _modelMatrix, _mvpMatrix;
    };
}

#endif // TENGINE_CUBE_RENDERING_STRATEGY_H