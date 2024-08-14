#include "GL/glew.h"

#include "CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

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
    glBindVertexArray(getCachedVao());

    glUseProgram(_shaderProgram);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 14);

    glUseProgram(0);

    glBindVertexArray(0);
}

void CubeRenderingStrategy::_prepareVbo()
{
    GLuint vbo;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices[] = {
        -1.f, 1.f, 1.f,   // Front-top-left
        1.f, 1.f, 1.f,    // Front-top-right
        -1.f, -1.f, 1.f,  // Front-bottom-left
        1.f, -1.f, 1.f,   // Front-bottom-right
        1.f, -1.f, -1.f,  // Back-bottom-right
        1.f, 1.f, 1.f,    // Front-top-right
        1.f, 1.f, -1.f,   // Back-top-right
        -1.f, 1.f, 1.f,   // Front-top-left
        -1.f, 1.f, -1.f,  // Back-top-left
        -1.f, -1.f, 1.f,  // Front-bottom-left
        -1.f, -1.f, -1.f, // Back-bottom-left
        1.f, -1.f, -1.f,  // Back-bottom-right
        -1.f, 1.f, -1.f,  // Back-top-left
        1.f, 1.f, -1.f    // Back-top-right
    };

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    setCachedVbo(vbo);
}

void CubeRenderingStrategy::_prepareVao()
{
    GLuint vao;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, getCachedVbo());

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);

    setCachedVao(vao);
}

void CubeRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->loadShader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
}