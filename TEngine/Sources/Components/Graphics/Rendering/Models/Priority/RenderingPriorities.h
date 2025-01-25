#ifndef TENGINE_RENDERINGPRIORITIES_H
#define TENGINE_RENDERINGPRIORITIES_H

namespace TEngine::Components::Graphics::Rendering::Models::Priority
{
    enum class RenderingPriority : char
    {
        NONE = 0,
        LOW = 1,
        MEDIUM = 2,
        HIGH = 3
    };
}

#endif // TENGINE_RENDERINGPRIORITIES_H