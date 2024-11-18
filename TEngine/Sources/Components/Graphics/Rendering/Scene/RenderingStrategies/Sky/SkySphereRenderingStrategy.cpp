#include "GL/glew.h"

#include "SkySphereRenderingStrategy.h"

#define VERTEX_BUFFER_NAME "SkySphereRenderingStrategy_VertexBuffer" + std::to_string(getId())
#define TEXTURE_BUFFER_NAME "SkySphereRenderingStrategy_TextureBuffer" + std::to_string(getId())
#define VAO_NAME "SkySphereRenderingStrategy_Vao" + std::to_string(getId())

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky;

SkySphereRenderingStrategy::SkySphereRenderingStrategy(std::shared_ptr<IShadersService> shadersService,
                                                       std::shared_ptr<IBuffersService> bufferCacheService,
                                                       std::shared_ptr<ITexturesService> texturesService) : 
                                                       _textureId(0),
                                                       _vao(0)
{
}

SkySphereRenderingStrategy::~SkySphereRenderingStrategy()
{
    if (_textureId != 0)
    {
        _texturesService->release(_textureId);
    }

    _releaseBuffers();
}

void SkySphereRenderingStrategy::setTexture(const std::string &texturePath)
{
    _textureId = _texturesService->take(texturePath);
}

void SkySphereRenderingStrategy::setSphere(float radius, int sectorCount, int stackCount)
{
    _releaseBuffers();

    std::vector<float> vertices = _generateHalfSphereVertices(radius, sectorCount, stackCount);

    // setup vertex vbo
    auto verextVbo = _bufferCacheService->takeVbo(VERTEX_BUFFER_NAME);
    glBindBuffer(GL_ARRAY_BUFFER, verextVbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // setup uv vbo
    auto textureVbo = _bufferCacheService->takeVbo(TEXTURE_BUFFER_NAME);
    glBindBuffer(GL_ARRAY_BUFFER, textureVbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // setup vao
    auto vao = _bufferCacheService->takeVao(VAO_NAME);
    glBindVertexArray(vao);


}

void SkySphereRenderingStrategy::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
}

std::vector<float> SkySphereRenderingStrategy::_generateHalfSphereVertices(float radius, int sectorCount, int stackCount)
{
    std::vector<float> vertices;
    float x, y, z, xy; // vertex position
    float sectorStep = 2 * M_PI / sectorCount;
    float stackStep = M_PI / stackCount;
    float sectorAngle, stackAngle;

    for (int i = 0; i <= stackCount / 2; ++i)
    {
        stackAngle = M_PI / 2 - i * stackStep; // starting from pi/2 to 0
        xy = radius * cosf(stackAngle);        // r * cos(u)
        z = radius * sinf(stackAngle);         // r * sin(u)

        for (int j = 0; j <= sectorCount; ++j)
        {
            sectorAngle = j * sectorStep; // starting from 0 to 2pi

            x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
            y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)
            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }
    }
    return vertices;
}

void SkySphereRenderingStrategy::_releaseBuffers()
{
    if (_bufferCacheService->existsVao(VERTEX_BUFFER_NAME))
    {
        _bufferCacheService->releaseVao(VERTEX_BUFFER_NAME);
    }

    if (_bufferCacheService->existsVbo(VERTEX_BUFFER_NAME))
    {
        _bufferCacheService->releaseVbo(VERTEX_BUFFER_NAME);
    }
}