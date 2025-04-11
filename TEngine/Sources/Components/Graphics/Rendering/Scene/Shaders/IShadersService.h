#ifndef TENGINE_ISHADERSSERVICE_H
#define TENGINE_ISHADERSSERVICE_H

#include "string"

#ifdef __ANDROID__
#include <EGL/egl.h>
#else
#include <GL/gl.h>
#endif

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