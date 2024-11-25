#ifndef TENGINE_ISOLIDBOXRENDERINGSTRATEGY_H
#define TENGINE_ISOLIDBOXRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/RenderingMixins/IPhysicsRenderingAware.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid
{
    class ISolidboxRenderingStrategy : public virtual RenderingMixins::IPhysicsRenderingAware
    {
    public:
        virtual void setIsVisualizationEnabled(bool value) = 0;
    };
}

#endif // TENGINE_ISOLIDBOXRENDERINGSTRATEGY_H