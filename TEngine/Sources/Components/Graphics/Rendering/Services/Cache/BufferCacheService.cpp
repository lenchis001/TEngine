#include "GL/glew.h"

#include "BufferCacheService.h"

#include "cassert"

using namespace TEngine::Components::Graphics::Rendering::Services::Cache;

BufferCacheService::~BufferCacheService()
{
    assert(_vboCache.empty() && "Cache is not empty!");
}

bool BufferCacheService::existsVbo(const std::string &name) const
{
    auto hash = _hashGenerator(name);

    return _vboCache.find(hash) != _vboCache.end();
}

GLuint BufferCacheService::getVbo(const std::string &name)
{
    assert(existsVbo(name) && "Value does not exist!");

    auto hash = _hashGenerator(name);

    return _vboCache[hash];
}

GLuint BufferCacheService::createVbo(const std::string &name)
{
    assert(!existsVbo(name) && "Value does not exist!");

    auto hash = _hashGenerator(name);

    GLuint vbo;

    glGenBuffers(1, &vbo);

    _vboCache[hash] = vbo;

    return vbo;
}

void BufferCacheService::removeVbo(const std::string &name)
{
    assert(existsVbo(name) && "Value does not exist!");

    auto hash = _hashGenerator(name);

    _vboUsagesCounter[hash]--;

    if (_vboUsagesCounter[hash] == 0)
    {
        auto vbo = _vboCache[hash];

        _vboCache.erase(hash);
        _vboUsagesCounter.erase(hash);

        glDeleteBuffers(1, &vbo);
    }
}

bool BufferCacheService::existsVao(const std::string &name) const
{
    auto hash = _hashGenerator(name);

    return _vaoCache.find(hash) != _vaoCache.end();
}

GLuint BufferCacheService::getVao(const std::string &name)
{
    assert(existsVao(name) && "Value does not exist!");

    auto hash = _hashGenerator(name);

    return _vaoCache[hash];
}

GLuint BufferCacheService::createVao(const std::string &name)
{
    assert(!existsVao(name) && "Value does not exist!");

    auto hash = _hashGenerator(name);

    GLuint vao;

    glGenVertexArrays(1, &vao);

    _vaoCache[hash] = vao;

    return vao;
}

void BufferCacheService::removeVao(const std::string &name)
{
    assert(existsVao(name) && "Value does not exist!");

    auto hash = _hashGenerator(name);

    _vaoUsagesCounter[hash]--;

    if (_vaoUsagesCounter[hash] == 0)
    {
        auto vao = _vaoCache[hash];

        _vaoCache.erase(hash);
        _vaoUsagesCounter.erase(hash);

        glDeleteVertexArrays(1, &vao);
    }
}