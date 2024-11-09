#ifndef TENGINE_SHADERSERVICE_H
#define TENGINE_SHADERSERVICE_H

#include "IShadersService.h"

#include "string"
#include "unordered_map"

namespace TEngine::Components::Graphics::Rendering::Scene::Shaders
{
    class ShadersService : public IShadersService
    {
    public:
        ShadersService() = default;
        ~ShadersService() override;

        GLuint take(const std::string &vertexShaderFile, const std::string& fragmentShaderFile) override;

        void release(GLuint programId) override;
    private:
        std::string _readShader(const std::string& shaderFile);

        std::unordered_map<std::string, std::size_t> _usagesCounter;
        std::unordered_map<std::string, GLuint> _shaderPrograms;
    };
}

#endif // TENGINE_SHADERSERVICE_H