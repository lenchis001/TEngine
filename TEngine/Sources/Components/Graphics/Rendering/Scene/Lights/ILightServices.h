#ifndef TENGINE_ILIGHTSERVICES_H
#define TENGINE_ILIGHTSERVICES_H

#include <memory>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

#include "Components/Graphics/Rendering/Models/Lights/IPointLight.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Lights {
    class ILightServices {
    public:
        virtual ~ILightServices() = default;

        virtual void update() = 0;

        virtual void updateTrackingObjectState(int id, const Graphics::Models::Vector3df& position, const Graphics::Models::Vector3df& size) = 0;

		virtual std::shared_ptr<Rendering::Models::Lights::IPointLight> addPointLight(const Graphics::Models::Vector3df& position, const Graphics::Models::Vector3df& diffuseColor, float radius) = 0;
    };
}

#endif // TENGINE_ILIGHTSERVICES_H