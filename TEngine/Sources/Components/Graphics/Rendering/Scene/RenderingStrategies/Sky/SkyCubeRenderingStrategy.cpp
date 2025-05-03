#include "SkyCubeRenderingStrategy.h"

#define VERTEX_SHADER_SOURCE "bundle://BuildinResources/Shaders/SkyBox/VertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "bundle://BuildinResources/Shaders/SkyBox/FragmentShader.glsl"

#define VERTEX_BUFFER_NAME "SkySphereRenderingStrategy_VertexBuffer" + std::to_string(getId())
#define TEXTURE_BUFFER_NAME "SkySphereRenderingStrategy_TextureBuffer" + std::to_string(getId())
#define VAO_NAME "SkySphereRenderingStrategy_Vao" + std::to_string(getId())

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky;

SkyCubeRenderingStrategy::
    SkyCubeRenderingStrategy(std::shared_ptr<IShadersService> shadersService,
                               std::shared_ptr<IBuffersService> bufferCacheService,
                               std::shared_ptr<ITexturesService> texturesService,
                               OnDeleteCallback onDeleteCallback)
    : RenderingStrategyBase(onDeleteCallback),
      _shadersService(shadersService),
      _bufferCacheService(bufferCacheService),
      _texturesService(texturesService),
      _textureId(0),
      _vao(0),
      _sectorCount(0)
{
    _prepareShader();
}

SkyCubeRenderingStrategy::~SkyCubeRenderingStrategy()
{
    if (_textureId != 0)
    {
        _texturesService->release(_textureId);
    }

    _releaseBuffers();

    _shadersService->release(_shaderProgram);
}

void SkyCubeRenderingStrategy::setTexture(
    const std::string &rightTexturePath,
    const std::string &leftTexturePath,
    const std::string &topTexturePath,
    const std::string &bottomTexturePath,
    const std::string &frontTexturePath,
    const std::string &backTexturePath)
{
    if (_textureId != 0)
    {
        _texturesService->release(_textureId);
    }

    _textureId = _texturesService->takeCubeMap(
        rightTexturePath,
        leftTexturePath,
        topTexturePath,
        bottomTexturePath,
        frontTexturePath,
        backTexturePath);
}

void SkyCubeRenderingStrategy::setSize(float size)
{
    _releaseBuffers();

    // setup vertex vbo
    std::vector<float> vertices = _generateCubeVertices(size);
    auto vertexVbo = _bufferCacheService->takeVbo(VERTEX_BUFFER_NAME);
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // setup vao
    _vao = _bufferCacheService->takeVao(VAO_NAME);
    glBindVertexArray(_vao);

    // bind vertex vbo
    glBindBuffer(GL_ARRAY_BUFFER, vertexVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

std::type_index SkyCubeRenderingStrategy::getType() const
{
    return typeid(SkyCubeRenderingStrategy);
}

RenderingPriority SkyCubeRenderingStrategy::getRenderingPriority() const
{
    return RenderingPriority::MEDIUM;
}

std::string SkyCubeRenderingStrategy::_getDefaultName() const
{
    return "SkySphere";
}

void SkyCubeRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    glBindVertexArray(_vao);

    glUseProgram(_shaderProgram);

    glUniformMatrix4fv(_matrixShaderId, 1, GL_FALSE, getMvpMatrix().getInternalData());
    glUniform1i(_cubeSamplerShaderId, 0);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, _textureId);

    glDrawArrays(GL_TRIANGLES, 0, 36);

#ifdef TENGINE_DEBUG
    // check for errors
    GLenum error = glGetError();
    if (error != GL_NO_ERROR)
    {
        std::cerr << "OpenGL error during rendering: " << error << std::endl;
    }
#endif

    glUseProgram(0);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    glBindVertexArray(0);
}

std::vector<float> SkyCubeRenderingStrategy::_generateCubeVertices(float size)
{
    std::vector<float> vertices =
        {

            // positions
            -1.0f, 1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,

            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,

            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,

            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f

        };

    return vertices;
}

void SkyCubeRenderingStrategy::_releaseBuffers()
{
    if (_bufferCacheService->existsVao(VAO_NAME))
    {
        _bufferCacheService->releaseVao(VAO_NAME);
    }

    if (_bufferCacheService->existsVbo(VERTEX_BUFFER_NAME))
    {
        _bufferCacheService->releaseVbo(VERTEX_BUFFER_NAME);
    }
}

void SkyCubeRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->take(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

    _matrixShaderId = glGetUniformLocation(_shaderProgram, "MVP");
    _cubeSamplerShaderId = glGetUniformLocation(_shaderProgram, "skybox");
}