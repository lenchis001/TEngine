#include "BufferCacheAware.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

GLuint BufferCacheAware::_cachedVbo = 0;
GLuint BufferCacheAware::_cachedVao = 0;

bool BufferCacheAware::isCachedFilled()
{
    return _cachedVbo != 0 && _cachedVao != 0;
}

GLuint BufferCacheAware::getCachedVbo()
{
    return _cachedVbo;
}

void BufferCacheAware::setCachedVbo(GLuint vbo)
{
    _cachedVbo = vbo;
}

GLuint BufferCacheAware::getCachedVao()
{
    return _cachedVao;
}

void BufferCacheAware::setCachedVao(GLuint vao)
{
    _cachedVao = vao;
}