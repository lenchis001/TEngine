#ifndef TENGINE_BUFFER_CACHE_AWARE_H
#define TENGINE_BUFFER_CACHE_AWARE_H

#include "GLFW/glfw3.h"

#include "typeinfo.h"

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives
{
    class BufferCacheAware
    {
    protected:
        BufferCacheAware(const std::type_info &userType);
        ~BufferCacheAware();

        bool isCachedFilled();

        GLuint getCachedVbo(std::size_t index = 0);

        void setCachedVbo(GLuint vbo, std::size_t index = 0);

        GLuint getCachedVao();

        void setCachedVao(GLuint vao);

    private:
        bool _existsInVAOs() const;
        bool _existsInVBOs() const;

        std::size_t _typeHash;
    };
}

#endif // TENGINE_BUFFER_CACHE_AWARE_H