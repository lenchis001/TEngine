#ifndef TENGINE_ISKYSPHERERENDERINGSTRATEGY_H
#define TENGINE_ISKYSPHERERENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

#include <memory>
#include <vector>

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky
{
    class ISkySphereRenderingStrategy : public virtual IRenderingStrategy
    {
    public:
        void setTexture(const std::string &texturePath);

        void setSphere(float radius, int sectorCount);
    };
} // namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies

#endif // TENGINE_ISKYSPHERERENDERINGSTRATEGY_H