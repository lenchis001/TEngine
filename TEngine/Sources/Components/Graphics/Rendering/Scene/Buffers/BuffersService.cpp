#include "BuffersService.h"

#include <cassert>

using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;

BuffersService::~BuffersService()
{
    assert(_vboCache.empty() && "Cache is not empty!");
    assert(_vaoCache.empty() && "Cache is not empty!");
}

bool BuffersService::existsVbo(const std::string &name) const
{
    auto hash = _hashGenerator(name);

    return _vboCache.find(hash) != _vboCache.end();
}

GLuint BuffersService::getVbo(const std::string &name)
{
    assert(existsVbo(name) && "VBO does not exist!");

    auto hash = _hashGenerator(name);

    return _vboCache[hash];
}

GLuint BuffersService::takeVbo(const std::string &name)
{
    auto hash = _hashGenerator(name);

    if (existsVbo(name))
    {
        _vboUsagesCounter[hash]++;

        return _vboCache[hash];
    }

    GLuint vbo;

    glGenBuffers(1, &vbo);

    _vboCache[hash] = vbo;
    _vboUsagesCounter[hash] = 1;

    return vbo;
}

void BuffersService::releaseVbo(const std::string &name)
{
    assert(existsVbo(name) && "VBO does not exist!");

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

bool BuffersService::existsVao(const std::string &name) const
{
    auto hash = _hashGenerator(name);

    return _vaoCache.find(hash) != _vaoCache.end();
}

GLuint BuffersService::getVao(const std::string &name)
{
    assert(existsVao(name) && "VAO does not exist!");

    auto hash = _hashGenerator(name);

    return _vaoCache[hash];
}

GLuint BuffersService::takeVao(const std::string &name)
{
    auto hash = _hashGenerator(name);

    if (existsVao(name))
    {
        _vaoUsagesCounter[hash]++;

        return _vaoCache[hash];
    }

    GLuint vao;

    glGenVertexArrays(1, &vao);

    _vaoCache[hash] = vao;
    _vaoUsagesCounter[hash] = 1;

    return vao;
}

void BuffersService::releaseVao(const std::string &name)
{
    assert(existsVao(name) && "VAO does not exist!");

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