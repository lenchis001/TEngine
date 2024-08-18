#include "BufferCacheAware.h"
#include "map"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

std::map<std::size_t, GLuint> globalVAOs;
std::map<std::size_t, std::map<std::size_t, GLuint>> globalVBOs;

BufferCacheAware::BufferCacheAware(const std::type_info &userType) : _typeHash(userType.hash_code()) {}

BufferCacheAware::~BufferCacheAware()
{
    globalVAOs.erase(_typeHash);
    globalVBOs.erase(_typeHash);
}

bool BufferCacheAware::isCachedFilled()
{
    return _existsInVAOs() && _existsInVBOs();
}

GLuint BufferCacheAware::getCachedVbo(std::size_t index)
{
    return globalVBOs[_typeHash].at(index);
}

void BufferCacheAware::setCachedVbo(GLuint vbo, std::size_t index)
{
    if (!_existsInVBOs())
    {
        globalVBOs[_typeHash] = std::map<std::size_t, GLuint>();
    }

    globalVBOs[_typeHash][index] = vbo;
}

GLuint BufferCacheAware::getCachedVao()
{
    return globalVAOs[_typeHash];
}

void BufferCacheAware::setCachedVao(GLuint vao)
{
    globalVAOs[_typeHash] = vao;
}

bool BufferCacheAware::_existsInVAOs() const
{
    return globalVAOs.find(_typeHash) != globalVAOs.end();
}

bool BufferCacheAware::_existsInVBOs() const
{
    return globalVBOs.find(_typeHash) != globalVBOs.end();
}
