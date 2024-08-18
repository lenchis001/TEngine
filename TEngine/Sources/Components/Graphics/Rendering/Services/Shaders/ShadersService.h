#ifndef TENGINE_SHADERSERVICE_H
#define TENGINE_SHADERSERVICE_H

#include "IShadersService.h"

#include "string"
#include "map"

namespace TEngine::Components::Graphics::Rendering::Services::Shaders
{
    class ShadersService : public IShadersService
    {
    public:
        ShadersService() = default;
        ~ShadersService() override;

        GLuint loadShader(const std::string &vertexShaderFile, const std::string& fragmentShaderFile) override;
    private:
        std::string readShader(const std::string& shaderFile);

        std::map<std::string, GLuint> _shaderPrograms;
    };
}

#endif // TENGINE_SHADERSERVICE_H