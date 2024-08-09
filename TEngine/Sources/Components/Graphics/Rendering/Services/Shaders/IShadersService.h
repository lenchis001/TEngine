#ifndef TENGINE_ISHADERSSERVICE_H
#define TENGINE_ISHADERSSERVICE_H

#include "string"

#include "GLFW/glfw3.h"

namespace TEngine::Components::Graphics::Rendering::Services::Shaders
{
    class IShadersService
    {
    public:
        virtual ~IShadersService() = default;

        virtual GLuint loadShader(const std::string &vertexShaderFile, const std::string& fragmentShaderFile) = 0;
    };
}

#endif // TENGINE_ISHADERSSERVICE_H