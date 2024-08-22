#include "GL/glew.h"

#include "CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

#define VERTEX_SHADER_SOURCE "BuildinResources/Shaders/SimpleVertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "BuildinResources/Shaders/SimpleFragmentShader.glsl"

#define VERTEX_VBO_INDEX 0
#define COLOR_VBO_INDEX 1

CubeRenderingStrategy::CubeRenderingStrategy(
    std::shared_ptr<IRenderableObject> cube,
    std::shared_ptr<IShadersService> shadersService,
    std::shared_ptr<Image> image)
    : BufferCacheAware(typeid(CubeRenderingStrategy)), _cube(cube), _shadersService(shadersService)
{
    _vpMatrix = Matrix4x4f(1.f);
    _modelMatrix = Matrix4x4f(1.f);
    _mvpMatrix = Matrix4x4f(1.f);

    if (!isCachedFilled())
    {
        _prepareVertexVbo();
        _prepareTexture(image);
        _prepareUvVbo();
        _prepareVao();
    }

    _prepareShader();
}

void CubeRenderingStrategy::render(const Matrix4x4f &vpMatrix)
{
    glBindVertexArray(getCachedVao());

    glUseProgram(_shaderProgram);

    const auto &modelMatrix = _cube->getModelMatrix();
    if (_vpMatrix != vpMatrix || _modelMatrix != modelMatrix)
    {
        _vpMatrix = vpMatrix;
        _modelMatrix = modelMatrix;

        _mvpMatrix = vpMatrix * modelMatrix;
    }

    glUniformMatrix4fv(_matrixShaderId, 1, GL_FALSE, _mvpMatrix.getInternalData());
    glUniform1i(_textureSamplerShaderId, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6 /*sides*/ * 2 /*triangles in every one*/ * 3 /*verteces in every one*/);

    glUseProgram(0);

    glBindVertexArray(0);
}

void CubeRenderingStrategy::_prepareVertexVbo()
{
    GLuint vbo;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    setCachedVbo(vbo, VERTEX_VBO_INDEX);
}

void CubeRenderingStrategy::_prepareTexture(std::shared_ptr<Image> image)
{
    glGenTextures(1, &_textureId);
    glBindTexture(GL_TEXTURE_2D, _textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->getWidth(), image->getHeight(), 0, GL_RGB, GL_UNSIGNED_BYTE, image->getData());

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void CubeRenderingStrategy::_prepareUvVbo()
{
    GLuint vbo;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    static const GLfloat uvData[] = {
        0.000059f, 1.0f - 0.000004f,
        0.000103f, 1.0f - 0.336048f,
        0.335973f, 1.0f - 0.335903f,
        1.000023f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f,
        0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f,
        0.336024f, 1.0f - 0.671877f,
        0.667969f, 1.0f - 0.671889f,
        1.000023f, 1.0f - 0.000013f,
        0.668104f, 1.0f - 0.000013f,
        0.667979f, 1.0f - 0.335851f,
        0.000059f, 1.0f - 0.000004f,
        0.335973f, 1.0f - 0.335903f,
        0.336098f, 1.0f - 0.000071f,
        0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f,
        0.336024f, 1.0f - 0.671877f,
        1.000004f, 1.0f - 0.671847f,
        0.999958f, 1.0f - 0.336064f,
        0.667979f, 1.0f - 0.335851f,
        0.668104f, 1.0f - 0.000013f,
        0.335973f, 1.0f - 0.335903f,
        0.667979f, 1.0f - 0.335851f,
        0.335973f, 1.0f - 0.335903f,
        0.668104f, 1.0f - 0.000013f,
        0.336098f, 1.0f - 0.000071f,
        0.000103f, 1.0f - 0.336048f,
        0.000004f, 1.0f - 0.671870f,
        0.336024f, 1.0f - 0.671877f,
        0.000103f, 1.0f - 0.336048f,
        0.336024f, 1.0f - 0.671877f,
        0.335973f, 1.0f - 0.335903f,
        0.667969f, 1.0f - 0.671889f,
        1.000004f, 1.0f - 0.671847f,
        0.667979f, 1.0f - 0.335851f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(uvData), uvData, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    setCachedVbo(vbo, COLOR_VBO_INDEX);
}

void CubeRenderingStrategy::_prepareVao()
{
    GLuint vao;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // Bind and activate vertex VBO
    glBindBuffer(GL_ARRAY_BUFFER, getCachedVbo(VERTEX_VBO_INDEX));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Bind and activate UV VBO
    glBindBuffer(GL_ARRAY_BUFFER, getCachedVbo(COLOR_VBO_INDEX));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setCachedVao(vao);
}

void CubeRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->loadShader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

    _matrixShaderId = glGetUniformLocation(_shaderProgram, "MVP");
    _textureSamplerShaderId = glGetUniformLocation(_shaderProgram, "textureSampler");
}