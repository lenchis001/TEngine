#ifndef TENGINE_ISKY_CUBE_RENDERING_STRATEGY_H
#define TENGINE_ISKY_CUBE_RENDERING_STRATEGY_H

#include <memory>
#include <vector>

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky
{
    class ISkyCubeRenderingStrategy : public virtual IRenderingStrategy
    {
    public:
        void setTexture(const std::string &texturePath);

        void setSphere(float radius, int sectorCount);
    };
} // namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies

#endif // TENGINE_ISKY_CUBE_RENDERING_STRATEGY_H