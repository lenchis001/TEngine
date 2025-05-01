#include "SolidboxRenderingStrategy.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Primitives/CubeRenderingStrategy.h"

#define VERTEX_VBO_NAME "SolidboxRenderingStrategy_VertexVbo"
#define VAO_NAME "SolidboxRenderingStrategy_Vao"

#define VERTEX_SHADER_SOURCE "buildin_bundle://BuildinResources/Shaders/Solidbox/VertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "buildin_bundle://BuildinResources/Shaders/Solidbox/FragmentShader.glsl"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;

SolidboxRenderingStrategy::SolidboxRenderingStrategy(
    std::shared_ptr<IShadersService> shadersService,
    std::shared_ptr<IBuffersService> bufferCacheService,
    std::shared_ptr<IPhysicsService> physicsService,
    OnDeleteCallback onDeleteCallback)
    : PhysicsRenderingStrategyBase(physicsService, onDeleteCallback),
      _isVisualizationEnabled(false),
      _shadersService(shadersService),
      _bufferCacheService(bufferCacheService)
{
    _prepareVertexVbo();
    _prepareVao();
    _prepareShader();
}

SolidboxRenderingStrategy::~SolidboxRenderingStrategy()
{
    _shadersService->release(_shaderProgram);

    _bufferCacheService->releaseVao(VAO_NAME);
    _bufferCacheService->releaseVbo(VERTEX_VBO_NAME);
}

std::type_index SolidboxRenderingStrategy::getType() const
{
    return typeid(SolidboxRenderingStrategy);
}

RenderingPriority SolidboxRenderingStrategy::getRenderingPriority() const
{
    return _isVisualizationEnabled ? RenderingPriority::LOW : RenderingPriority::NONE;
}

std::vector<float> SolidboxRenderingStrategy::_getVertices() const
{
    return {
        // bottom corner
        -0.5,
        -0.5,
        -0.5,
        // top corner
        0.5,
        0.5,
        0.5,
    };
}

void SolidboxRenderingStrategy::setIsVisualizationEnabled(bool value)
{
    _isVisualizationEnabled = value;
}

std::string SolidboxRenderingStrategy::_getDefaultName() const
{
    return "Solidbox";
}

void SolidboxRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    if (_isVisualizationEnabled)
    {
        glBindVertexArray(_vao);

        glUseProgram(_shaderProgram);

        glUniformMatrix4fv(_matrixShaderId, 1, GL_FALSE, getMvpMatrix().getInternalData());

        glDrawArrays(GL_TRIANGLES, 0, 6 /*sides*/ * 2 /*triangles in every one*/ * 3 /*verteces in every one*/);

        glUseProgram(0);
        glBindTexture(GL_TEXTURE_2D, 0);
        glBindVertexArray(0);
    }
}

void SolidboxRenderingStrategy::_prepareVertexVbo()
{
    GLuint vbo = _bufferCacheService->takeVbo(VERTEX_VBO_NAME);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(float), _vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void SolidboxRenderingStrategy::_prepareVao()
{
    _vao = _bufferCacheService->takeVao(VAO_NAME);

    glBindVertexArray(_vao);

    // Bind and activate vertex VBO
    glBindBuffer(GL_ARRAY_BUFFER, GET_VBO(VERTEX_VBO_NAME));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SolidboxRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->take(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

    _matrixShaderId = glGetUniformLocation(_shaderProgram, "MVP");
}

std::vector<float> SolidboxRenderingStrategy::_vertices = {
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