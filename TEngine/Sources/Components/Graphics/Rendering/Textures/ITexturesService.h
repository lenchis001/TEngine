#ifndef TENGINE_ITEXTURESSERVICE_H
#define TENGINE_ITEXTURESSERVICE_H

#include <string>

#include "Components/Graphics/PlatformWrapping/GlWrapper.h"

namespace TEngine::Components::Graphics::Rendering::Textures
{
    class ITexturesService
    {
    public:
        virtual ~ITexturesService() = default;

        virtual void initialize() = 0;

        virtual GLuint take(const std::string &textureFile) = 0;

        virtual GLuint takeCubeMap(
            const std::string &rightTexturePath,
            const std::string &leftTexturePath,
            const std::string &topTexturePath,
            const std::string &bottomTexturePath,
            const std::string &frontTexturePath,
            const std::string &backTexturePath) = 0;

        virtual void release(GLuint textureId) = 0;

        virtual bool isAlphaChannelAware(GLuint textureId) = 0;
    };
}

#endif // TENGINE_ITEXTURESSERVICE_H