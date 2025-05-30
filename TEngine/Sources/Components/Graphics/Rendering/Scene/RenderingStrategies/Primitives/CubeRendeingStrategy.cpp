#include <algorithm>

#include "CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;

#define VERTEX_SHADER_SOURCE "bundle://BuildinResources/Shaders/SimpleVertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "bundle://BuildinResources/Shaders/SimpleFragmentShader.glsl"

#define VERTEX_VBO_NAME "CubeRenderingStrategy_VertexVbo"
#define UV_VBO_NAME "CubeRenderingStrategy_ColorVbo"
#define VAO_NAME "CubeRenderingStrategy_Vao"

CubeRenderingStrategy::CubeRenderingStrategy(
    std::shared_ptr<IShadersService> shadersService,
    std::shared_ptr<IBuffersService> bufferCacheService,
    std::shared_ptr<ITexturesService> texturesService,
    std::shared_ptr<IPhysicsService> physicsService,
    OnDeleteCallback onDeleteCallback)
    : PhysicsRenderingStrategyBase(physicsService, onDeleteCallback),
      _shadersService(shadersService),
      _bufferCacheService(bufferCacheService),
      _texturesService(texturesService),
      _textureId(0)
{
    _prepareVertexVbo();
    _prepareUvVbo();
    _prepareVao();

    _prepareShader();
}

CubeRenderingStrategy::~CubeRenderingStrategy()
{
    if (_textureId)
    {
        _texturesService->release(_textureId);
    }

    _shadersService->release(_shaderProgram);

    RELEASE_VAO(VAO_NAME);

    RELEASE_VBO(VERTEX_VBO_NAME);
    RELEASE_VBO(UV_VBO_NAME);
}

std::type_index CubeRenderingStrategy::getType() const
{
    return typeid(CubeRenderingStrategy);
}

void CubeRenderingStrategy::setPosition(const Vector3df &position)
{
    PhysicsRenderingStrategyBase::setPosition(position);
}

void CubeRenderingStrategy::setRotation(const Vector3df &rotation)
{
    PhysicsRenderingStrategyBase::setRotation(rotation);
}

const std::string &CubeRenderingStrategy::getTexture() const
{
    return _texturePath;
}

void CubeRenderingStrategy::setTexture(const std::string &texturePath)
{
    if (_textureId)
    {
        _texturesService->release(_textureId);
        _textureId = 0;
    }

    _texturePath = texturePath;

    _textureId = _texturesService->take(_texturePath);
}

RenderingPriority CubeRenderingStrategy::getRenderingPriority() const
{
    if (!_textureId)
    {
        return RenderingPriority::NONE;
    }

    if (_texturesService->isAlphaChannelAware(_textureId))
    {
        return RenderingPriority::LOW;
    }
    else
    {
        return RenderingPriority::HIGH;
    }
}

std::string CubeRenderingStrategy::_getDefaultName() const
{
    return "Cube";
}

void CubeRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    if (_textureId)
    {
        glBindVertexArray(_vao);

        glUseProgram(_shaderProgram);

        glUniformMatrix4fv(_matrixShaderId, 1, GL_FALSE, getMvpMatrix().getInternalData());
        glUniform1i(_textureSamplerShaderId, 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, _textureId);

        glDrawArrays(GL_TRIANGLES, 0, 6 /*sides*/ * 2 /*triangles in every one*/ * 3 /*verteces in every one*/);

        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }
}

std::vector<float> CubeRenderingStrategy::_getVertices() const
{
    return _vertices;
}

void CubeRenderingStrategy::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    PhysicsRenderingStrategyBase::_onAttachedToParent(parent);
}

void CubeRenderingStrategy::_onDetachedFromParent()
{
    PhysicsRenderingStrategyBase::_onDetachedFromParent();
}

void CubeRenderingStrategy::_prepareVertexVbo()
{
    RETURN_IF_VBO_EXISTS(VERTEX_VBO_NAME);

    GLuint vbo = TAKE_VBO(VERTEX_VBO_NAME);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeRenderingStrategy::_prepareUvVbo()
{
    RETURN_IF_VBO_EXISTS(UV_VBO_NAME);

    GLuint vbo = TAKE_VBO(UV_VBO_NAME);

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
}

void CubeRenderingStrategy::_prepareVao()
{
    RETURN_IF_VAO_EXISTS(VAO_NAME, _vao);

    _vao = TAKE_VAO(VAO_NAME);

    glBindVertexArray(_vao);

    // Bind and activate vertex VBO
    glBindBuffer(GL_ARRAY_BUFFER, GET_VBO(VERTEX_VBO_NAME));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Bind and activate UV VBO
    glBindBuffer(GL_ARRAY_BUFFER, GET_VBO(UV_VBO_NAME));
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void CubeRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->take(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

    _matrixShaderId = glGetUniformLocation(_shaderProgram, "MVP");
    _textureSamplerShaderId = glGetUniformLocation(_shaderProgram, "textureSampler");
}

std::vector<float> CubeRenderingStrategy::_vertices = {
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    -0.5f, -0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, -0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, 0.5f, 0.5f,
    -0.5f, 0.5f, 0.5f,
    0.5f, -0.5f, 0.5f};