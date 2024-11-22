#ifndef TENGINE_ISKYSPHERERENDERINGSTRATEGY_H
#define TENGINE_ISKYSPHERERENDERINGSTRATEGY_H

#include <memory>
#include <vector>

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

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