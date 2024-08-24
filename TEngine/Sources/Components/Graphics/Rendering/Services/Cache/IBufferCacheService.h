#ifndef TENGINE_IBUFFER_CACHE_SERVICE_H
#define TENGINE_IBUFFER_CACHE_SERVICE_H

#include "string"

#include "GL/gl.h"

#define GET_VBO(name) _bufferCacheService->getVbo(name)
#define TAKE_VBO(name) _bufferCacheService->takeVbo(name)
#define RELEASE_VBO(name) _bufferCacheService->releaseVbo(name)
#define RETURN_IF_VBO_EXISTS(name) if(_bufferCacheService->existsVbo(name)) { TAKE_VBO(name); return; }

#define TAKE_VAO(name) _bufferCacheService->takeVao(name)
#define RELEASE_VAO(name) _bufferCacheService->releaseVao(name)
#define RETURN_IF_VAO_EXISTS(name, vao) if(_bufferCacheService->existsVao(name)) { vao = TAKE_VAO(name); return; }

namespace TEngine::Components::Graphics::Rendering::Services::Cache
{
    class IBufferCacheService
    {
    public:
        virtual ~IBufferCacheService() = default;

        virtual bool existsVbo(const std::string &name) const = 0;
        virtual GLuint getVbo(const std::string &name) = 0;
        virtual GLuint takeVbo(const std::string &name) = 0;
        virtual void releaseVbo(const std::string &name) = 0;

        virtual bool existsVao(const std::string &name) const = 0;
        virtual GLuint getVao(const std::string &name) = 0;
        virtual GLuint takeVao(const std::string &name) = 0;
        virtual void releaseVao(const std::string &name) = 0;
    };
}

#endif // TENGINE_IBUFFER_CACHE_SERVICE_H