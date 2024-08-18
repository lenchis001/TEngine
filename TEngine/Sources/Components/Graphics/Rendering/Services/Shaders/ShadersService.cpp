#include "GL/glew.h"

#include "ShadersService.h"

#include "fstream"

#include "GLFW/glfw3.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;

ShadersService::~ShadersService()
{
    for(auto& shaderProgram : _shaderPrograms)
    {
        glDeleteProgram(shaderProgram.second);
    }
}

GLuint ShadersService::loadShader(const std::string &vertexShaderFile, const std::string& fragmentShaderFile)
{
        if(_shaderPrograms.find(vertexShaderFile + fragmentShaderFile) != _shaderPrograms.end())
        {
            return _shaderPrograms[vertexShaderFile + fragmentShaderFile];
        }

        std::string vertex = readShader(vertexShaderFile);
        if(vertex.empty())
        {
            return 0;
        }
        std::string fragment = readShader(fragmentShaderFile);
        if(fragment.empty())
        {
            return 0;
        }

        GLuint shaderProgramId = glCreateProgram();
        
        const char* vertexShaderSource = vertex.c_str();
        
        GLuint vertexShaderId = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderId, 1, &vertexShaderSource, nullptr);
        glCompileShader(vertexShaderId);
        
        GLint success;
        glGetShaderiv(vertexShaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(vertexShaderId, 512, nullptr, infoLog);
            glDeleteShader(vertexShaderId);
            return 0;
        }
        
        glAttachShader(shaderProgramId, vertexShaderId);

        const char* fragmentShaderSource = fragment.c_str();
        
        GLuint fragmentShaderId = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShaderId, 1, &fragmentShaderSource, nullptr);
        glCompileShader(fragmentShaderId);
        
        glGetShaderiv(fragmentShaderId, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetShaderInfoLog(fragmentShaderId, 512, nullptr, infoLog);
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);
            return 0;
        }
        
        glAttachShader(shaderProgramId, fragmentShaderId);
        
        glLinkProgram(shaderProgramId);
        
        glGetProgramiv(shaderProgramId, GL_LINK_STATUS, &success);
        if (!success)
        {
            char infoLog[512];
            glGetProgramInfoLog(shaderProgramId, 512, nullptr, infoLog);
            glDeleteShader(vertexShaderId);
            glDeleteShader(fragmentShaderId);
            glDeleteProgram(shaderProgramId);
            return 0;
        }
        
        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        _shaderPrograms[vertexShaderFile + fragmentShaderFile] = shaderProgramId;
        
        return shaderProgramId;
}

std::string ShadersService::readShader(const std::string& shaderFile)
{
    std::ifstream file(shaderFile);
    if (!file.is_open())
    {
        return "";
    }

    // Read the entire file into a string
    std::string shader((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());

    file.close();

    return shader;
}