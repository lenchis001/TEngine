#ifndef TENGINE_SHADERPOINTLIGHT_H
#define TENGINE_SHADERPOINTLIGHT_H

namespace TEngine::Components::Graphics::Rendering::Scene::Models::Lights::Shader
{
    struct ShaderPointLight
    {
        alignas(16) float position[3];
        alignas(16) float color[3];
        float intensity;
    };
}

#endif // TENGINE_SHADERPOINTLIGHT_H