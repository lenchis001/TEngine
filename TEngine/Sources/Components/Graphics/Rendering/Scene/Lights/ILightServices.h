#ifndef TENGINE_ILIGHTSERVICES_H
#define TENGINE_ILIGHTSERVICES_H

#include <memory>

#include "Components/Graphics/Rendering/Models/Lights/IPointLight.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Lights {
    class ILightServices {
    public:
        virtual ~ILightServices() = default;

        virtual void update() = 0;

        virtual const std::shared_ptr<Graphics::Rendering::Models::Lights::IPointLight> getPointLight() const = 0;
    };
}

#endif // TENGINE_ILIGHTSERVICES_H