#ifndef TENGINE_IPOINTLIGHT_H
#define TENGINE_IPOINTLIGHT_H

#include "Components/Graphics/Models/Vector3d.h"

namespace TEngine::Components::Graphics::Rendering::Models::Lights {
    class IPointLight
    {
        public:
            virtual ~IPointLight() = default;

            virtual void setPosition(const Components::Graphics::Models::Vector3df &position) = 0;
            virtual const Components::Graphics::Models::Vector3df& getPosition() const = 0;
            
            virtual const Components::Graphics::Models::Vector3df& getDiffuseColor() const = 0;
    };
}

#endif // TENGINE_IPOINTLIGHT_H