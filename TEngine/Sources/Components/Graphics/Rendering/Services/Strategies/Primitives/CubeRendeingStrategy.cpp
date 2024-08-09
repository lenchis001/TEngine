#include "GL/glew.h"

#include "CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Strategies::Primitives;

#define VERTEX_SHADER_SOURCE "BuildinResources/Shaders/SimpleVertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "BuildinResources/Shaders/SimpleFragmentShader.glsl"

CubeRenderingStrategy::CubeRenderingStrategy(std::shared_ptr<IRenderableObject> cube, std::shared_ptr<IShadersService> shadersService)
    : _cube(cube), _shadersService(shadersService)
{
    _prepareVbo();
    _prepareVao();
    _prepareShader();
}

void CubeRenderingStrategy::render()
{
    glBindVertexArray(_vao);

    glUseProgram(_shaderProgram);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    glUseProgram(0);

    glBindVertexArray(0);
}

void CubeRenderingStrategy::_prepareVbo()
{
    glGenBuffers(1, &_vbo);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    float vertices[9] =
        {
            1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f,
            0.0f,
            0.0f,
            0.0f,
            1.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeRenderingStrategy::_prepareVao()
{
    glGenVertexArrays(1, &_vao);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

void CubeRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->loadShader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
}