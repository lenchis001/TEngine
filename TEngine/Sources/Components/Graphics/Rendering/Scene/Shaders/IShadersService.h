#ifndef TENGINE_ISHADERSSERVICE_H
#define TENGINE_ISHADERSSERVICE_H

#include <string>

#include "Components/Graphics/PlatformWrapping/GlWrapper.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Shaders
{
    class IShadersService
    {
    public:
        virtual ~IShadersService() = default;

        virtual GLuint take(const std::string &vertexShaderFile, const std::string& fragmentShaderFile) = 0;

        virtual void release(GLuint programId) = 0;
    };
}

#endif // TENGINE_ISHADERSSERVICE_H