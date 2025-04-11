#include "GL/glew.h"

#include "ShadersService.h"

#include "fstream"
#include "cassert"
#include "iostream"

#ifdef __ANDROID__
#include <EGL/egl.h>
#else
#include <GL/gl.h>
#endif

using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;

ShadersService::~ShadersService()
{
    assert(_shaderPrograms.empty() && "Shader programs cache is not empty!");
}

GLuint ShadersService::take(const std::string &vertexShaderFile, const std::string &fragmentShaderFile)
{
    auto shaderKey = vertexShaderFile + fragmentShaderFile;

    if (_shaderPrograms.find(shaderKey) == _shaderPrograms.end())
    {
        std::string vertex = _readShader(vertexShaderFile);
        if (vertex.empty())
        {
            assert(false && "Vertex shader not found!");
            return 0;
        }
        std::string fragment = _readShader(fragmentShaderFile);
        if (fragment.empty())
        {
            assert(false && "Fragment shader not found!");
            return 0;
        }

        GLuint shaderProgramId = glCreateProgram();

        const char *vertexShaderSource = vertex.c_str();

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
            std::cerr << infoLog << std::endl;
            return 0;
        }

        glAttachShader(shaderProgramId, vertexShaderId);

        const char *fragmentShaderSource = fragment.c_str();

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
            std::cerr << infoLog << std::endl;
            assert(false && "Fragment shader compilation failed!");
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
            std::cerr << infoLog << std::endl;
            assert(false && "Shader program linking failed!");
            return 0;
        }

        glDeleteShader(vertexShaderId);
        glDeleteShader(fragmentShaderId);

        _shaderPrograms[shaderKey] = shaderProgramId;
    }

    _usagesCounter[shaderKey]++;

    return _shaderPrograms[shaderKey];
}

void ShadersService::release(GLuint programId)
{
    for (auto &shaderProgram : _shaderPrograms)
    {
        if (shaderProgram.second == programId)
        {
            _usagesCounter[shaderProgram.first]--;

            if (_usagesCounter[shaderProgram.first] == 0)
            {
                glDeleteProgram(programId);
                _usagesCounter.erase(shaderProgram.first);
                _shaderPrograms.erase(shaderProgram.first);
            }

            return;
        }
    }

    assert(false && "Shader program not found!");
}

std::string ShadersService::_readShader(const std::string &shaderFile)
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