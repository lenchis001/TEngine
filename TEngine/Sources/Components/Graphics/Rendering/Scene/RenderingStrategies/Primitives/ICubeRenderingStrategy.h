#ifndef TENGINE_ICUBERENDERINGSTRATEGY_H
#define TENGINE_ICUBERENDERINGSTRATEGY_H

#include <string>

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Physics/IPhysicsRenderingAware.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives
{
    class ICubeRenderingStrategy : public virtual RenderingStrategies::Physics::IPhysicsRenderingAware
    {
    public:
        virtual const std::string &getTexture() const = 0;

        virtual void setTexture(const std::string &texturePath) = 0;
    };
}

#endif // TENGINE_ICUBERENDERINGSTRATEGY_H