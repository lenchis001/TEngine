#ifndef TENGINE_ILIGHTRENDERINGSTRATEGY_H
#define TENGINE_ILIGHTRENDERINGSTRATEGY_H

#include <vector>
#include <memory>

#include "Components/Graphics/Rendering/Scene/Models/Lights/IPointLight.h"
#include "Components/Graphics/Models/Vector3d.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light
{
    class ILightRenderingStrategy : public virtual IRenderingStrategy
    {
    public:
        virtual const Graphics::Models::Vector3df& getSize() const = 0;

        virtual void updatePointLights(const std::vector<std::shared_ptr<Graphics::Rendering::Scene::Models::Lights::IPointLight>>&& pointLights) = 0;
    };
}

#endif // TENGINE_ILIGHTRENDERINGSTRATEGY_H
