#ifndef TENGINE_BUFFER_CACHE_AWARE_H
#define TENGINE_BUFFER_CACHE_AWARE_H

#include "GLFW/glfw3.h"

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives
{
    class BufferCacheAware
    {
    protected:
        static bool isCachedFilled();

        static GLuint getCachedVbo();

        static void setCachedVbo(GLuint vbo);

        static GLuint getCachedVao();

        static void setCachedVao(GLuint vao);

    private:
        static GLuint _cachedVbo;
        static GLuint _cachedVao;
    };
}

#endif // TENGINE_BUFFER_CACHE_AWARE_H