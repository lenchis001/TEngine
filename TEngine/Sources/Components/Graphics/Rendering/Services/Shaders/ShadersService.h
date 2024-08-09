#ifndef TENGINE_SHADERSERVICE_H
#define TENGINE_SHADERSERVICE_H

#include "IShadersService.h"

namespace TEngine::Components::Graphics::Rendering::Services::Shaders
{
    class ShadersService : public IShadersService
    {
    public:
        ShadersService() = default;
        ~ShadersService() override = default;

        GLuint loadShader(const std::string &vertexShaderFile, const std::string& fragmentShaderFile) override;
    private:
        std::string readShader(const std::string& shaderFile);
    };
}

#endif // TENGINE_SHADERSERVICE_H