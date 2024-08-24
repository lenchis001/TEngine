#ifndef TENGINE_IBUFFER_CACHE_SERVICE_H
#define TENGINE_IBUFFER_CACHE_SERVICE_H

#include "string"

#include "GL/gl.h"

#define RETURN_IF_VBO_EXISTS(name) if(_bufferCacheService->existsVbo(name)) { return; }
#define GET_VBO(name) _bufferCacheService->getVbo(name)
#define CREATE_VBO(name) _bufferCacheService->createVbo(name)
#define REMOVE_VBO(name) _bufferCacheService->removeVbo(name)

#define RETURN_IF_VAO_EXISTS(name, vao) if(_bufferCacheService->existsVao(name)) { vao = _bufferCacheService->getVao(name); return; }
#define CREATE_VAO(name) _bufferCacheService->createVao(name)
#define REMOVE_VAO(name) _bufferCacheService->removeVao(name)

namespace TEngine::Components::Graphics::Rendering::Services::Cache
{
    class IBufferCacheService
    {
    public:
        virtual ~IBufferCacheService() = default;

        virtual bool existsVbo(const std::string &name) const = 0;
        virtual GLuint getVbo(const std::string &name) = 0;
        virtual GLuint createVbo(const std::string &name) = 0;
        virtual void removeVbo(const std::string &name) = 0;

        virtual bool existsVao(const std::string &name) const = 0;
        virtual GLuint getVao(const std::string &name) = 0;
        virtual GLuint createVao(const std::string &name) = 0;
        virtual void removeVao(const std::string &name) = 0;
    };
}

#endif // TENGINE_IBUFFER_CACHE_SERVICE_H