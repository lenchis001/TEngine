#ifndef TENGINE_CUBE_RENDERING_STRATEGY_H
#define TENGINE_CUBE_RENDERING_STRATEGY_H

#include "memory"

#include "GLFW/glfw3.h"

#include "Components/Graphics/Rendering/Services/RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IRenderableObject.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"

#include "BufferCacheAware.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives
{
    class CubeRenderingStrategy : public BufferCacheAware, public IRenderingStrategy
    {
    public:
        CubeRenderingStrategy(std::shared_ptr<IRenderableObject> cube, std::shared_ptr<IShadersService> shadersService);

        void render(const Matrix4x4f& vpMatrix) override;

    private:
        void _prepareVertexVbo();
        void _prepareColorVbo();
        void _prepareVao();
        void _prepareShader();

        std::shared_ptr<IShadersService> _shadersService;

        std::shared_ptr<IRenderableObject> _cube;

        GLuint _shaderProgram, _matrixId;
    };
}

#endif // TENGINE_CUBE_RENDERING_STRATEGY_H