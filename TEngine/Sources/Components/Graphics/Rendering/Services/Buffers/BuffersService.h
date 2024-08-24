#ifndef TENGINE_BUFFERS_SERVICE_H
#define TENGINE_BUFFERS_SERVICE_H

#include "IBuffersService.h"

#include "map"
#include "string"

namespace TEngine::Components::Graphics::Rendering::Services::Buffers
{
    class BuffersService : public IBuffersService
    {
    public:
        ~BuffersService() override;

        bool existsVbo(const std::string &name) const override;
        GLuint getVbo(const std::string &name) override;
        GLuint takeVbo(const std::string &name) override;
        void releaseVbo(const std::string &name) override;

        bool existsVao(const std::string &name) const override;
        GLuint getVao(const std::string &name) override;
        GLuint takeVao(const std::string &name) override;
        void releaseVao(const std::string &name) override;

    private:
        std::hash<std::string> _hashGenerator;

        std::map<std::size_t, GLuint> _vboCache;
        std::map<std::size_t, std::size_t> _vboUsagesCounter;

        std::map<std::size_t, GLuint> _vaoCache;
        std::map<std::size_t, std::size_t> _vaoUsagesCounter;
    };
}

#endif // TENGINE_BUFFERS_SERVICE_H