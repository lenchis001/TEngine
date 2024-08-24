#ifndef TENGINE_BUFFER_CACHE_SERVICE_H
#define TENGINE_BUFFER_CACHE_SERVICE_H

#include "IBufferCacheService.h"

#include "map"
#include "string"

namespace TEngine::Components::Graphics::Rendering::Services::Cache
{
    class BufferCacheService : public IBufferCacheService
    {
    public:
        ~BufferCacheService() override;

        bool existsVbo(const std::string &name) const override;
        GLuint getVbo(const std::string &name) override;
        GLuint createVbo(const std::string &name) override;
        void removeVbo(const std::string &name) override;

        bool existsVao(const std::string &name) const override;
        GLuint getVao(const std::string &name) override;
        GLuint createVao(const std::string &name) override;
        void removeVao(const std::string &name) override;

    private:
        std::hash<std::string> _hashGenerator;

        std::map<std::size_t, GLuint> _vboCache;
        std::map<std::size_t, std::size_t> _vboUsagesCounter;

        std::map<std::size_t, GLuint> _vaoCache;
        std::map<std::size_t, std::size_t> _vaoUsagesCounter;
    };
}

#endif // TENGINE_BUFFER_CACHE_SERVICE_H