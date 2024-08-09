#ifndef TENGINE_CUBE_RENDERING_STRATEGY_H
#define TENGINE_CUBE_RENDERING_STRATEGY_H

#include "memory"

#include "GLFW/glfw3.h"

#include "Components/Graphics/Rendering/Services/Strategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IRenderableObject.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;

namespace TEngine::Components::Graphics::Rendering::Services::Strategies::Primitives
{
    class CubeRenderingStrategy : public IRenderingStrategy
    {
    public:
        CubeRenderingStrategy(std::shared_ptr<IRenderableObject> cube, std::shared_ptr<IShadersService> shadersService);

        void render() override;

    private:
        void _prepareVbo();
        void _prepareVao();
        void _prepareShader();

        std::shared_ptr<IShadersService> _shadersService;

        std::shared_ptr<IRenderableObject> _cube;

        GLuint _vao;
        GLuint _vbo;
        GLuint _shaderProgram;
    };
}

#endif // TENGINE_CUBE_RENDERING_STRATEGY_H