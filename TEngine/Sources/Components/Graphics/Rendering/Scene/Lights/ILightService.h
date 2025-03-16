#ifndef TENGINE_ILIGHTSERVICE_H
#define TENGINE_ILIGHTSERVICE_H

#include <memory>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Light/ILightRenderingStrategy.h"

#include "Components/Graphics/Rendering/Scene/Models/Lights/IPointLight.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Lights {
    class ILightService {
    public:
        virtual ~ILightService() = default;

        virtual void update() = 0;

        virtual void updateTrackingObjectState(std::shared_ptr<RenderingStrategies::Light::ILightRenderingStrategy> strategy) = 0;

        virtual void stopTracking(int id) = 0;

		virtual std::shared_ptr<Scene::Models::Lights::IPointLight> addPointLight(const Graphics::Models::Vector3df& position, const Graphics::Models::Vector3df& diffuseColor, float radius) = 0;
        virtual void removePointLight(const std::shared_ptr<Scene::Models::Lights::IPointLight> light) = 0;
    };
}

#endif // TENGINE_ILIGHTSERVICE_H