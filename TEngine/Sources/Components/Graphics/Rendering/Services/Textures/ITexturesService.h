#ifndef TENGINE_ITEXTURESSERVICE_H
#define TENGINE_ITEXTURESSERVICE_H

#include "string"

#include "GLFW/glfw3.h"

namespace TEngine::Components::Graphics::Rendering::Services::Textures
{
    class ITexturesService
    {
    public:
        virtual ~ITexturesService() = default;

        virtual void initialize() = 0;

        virtual GLuint take(const std::string &textureFile) = 0;

        virtual void release(GLuint textureId) = 0;
    };
}

#endif // TENGINE_ITEXTURESSERVICE_H