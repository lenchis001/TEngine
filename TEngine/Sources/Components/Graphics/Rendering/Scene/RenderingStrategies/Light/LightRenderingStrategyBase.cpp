#include "gl/glew.h"

#include "LightRenderingStrategyBase.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light;

LightRenderingStrategyBase::LightRenderingStrategyBase(std::shared_ptr<ILightService> lightService)
    : _lightService(lightService), _pointLightsBuffer(0)
{
}

void LightRenderingStrategyBase::updatePointLights(const std::vector<ShaderPointLight> &&pointLights)
{
    if (_pointLightsBuffer != 0)
    {
        glDeleteBuffers(1, &_pointLightsBuffer);
    }

    glGenBuffers(1, &_pointLightsBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, _pointLightsBuffer);

    _pointLightsAmount = pointLights.size();
    size_t bufferSize = pointLights.size() * sizeof(ShaderPointLight);

    glBufferData(GL_UNIFORM_BUFFER, bufferSize, pointLights.data(), GL_DYNAMIC_DRAW);

    glBindBufferBase(GL_UNIFORM_BUFFER, 1, _pointLightsBuffer);

    glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

GLuint LightRenderingStrategyBase::getPointLightsBuffer() const
{
    return _pointLightsBuffer;
}

GLuint LightRenderingStrategyBase::getPointLightsAmount() const
{
    return _pointLightsAmount;
}

Vector3df LightRenderingStrategyBase::_determineSize(const std::vector<float> &vertices)
{
    Vector3df min(0, 0, 0);
    Vector3df max(0, 0, 0);

    for (size_t i = 0; i < vertices.size(); i += 3)
    {
        min.setX(std::min(min.getX(), vertices[i]));
        min.setY(std::min(min.getY(), vertices[i + 1]));
        min.setZ(std::min(min.getZ(), vertices[i + 2]));

        max.setX(std::max(max.getX(), vertices[i]));
        max.setY(std::max(max.getY(), vertices[i + 1]));
        max.setZ(std::max(max.getZ(), vertices[i + 2]));
    }

    return Vector3df(
        std::abs(min.getX()) + std::abs(max.getX()),
        std::abs(min.getY()) + std::abs(max.getY()),
        std::abs(min.getZ()) + std::abs(max.getZ()));
}