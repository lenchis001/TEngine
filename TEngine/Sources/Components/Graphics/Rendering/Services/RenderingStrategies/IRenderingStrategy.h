#ifndef TENGINE_IRENDERINGSTRATEGY_H
#define TENGINE_IRENDERINGSTRATEGY_H

#include "Components/Graphics/Models/Matrix4x4.h"

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies
{
    class IRenderingStrategy
    {
    public:
        virtual void render(const Components::Graphics::Models::Matrix4x4f& vpMatrix) = 0;

        virtual ~IRenderingStrategy() = default;
    };
}

#endif // TENGINE_IRENDERINGSTRATEGY_H