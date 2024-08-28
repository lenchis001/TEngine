#ifndef TENGINE_ICAMERASTRATEGY_H
#define TENGINE_ICAMERASTRATEGY_H

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Models/Matrix4x4.h"
#include "Components/Graphics/Models/Parallelepiped.h"

namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies
{

    class ICameraStrategy
    {
    public:
        virtual const TEngine::Components::Graphics::Models::Vector3df &getPosition() const = 0;
        virtual void setPosition(const TEngine::Components::Graphics::Models::Vector3df& value) = 0;

        virtual const TEngine::Components::Graphics::Models::Vector3df &getTarget() const = 0;
        virtual void setTarget(const TEngine::Components::Graphics::Models::Vector3df& value) = 0;

        virtual void render() = 0;

        virtual const TEngine::Components::Graphics::Models::Matrix4x4f &getVpMatrix() const = 0;

        virtual const TEngine::Components::Graphics::Models::Parallelepipedf &getViewArea() const = 0;

        virtual void setAspectRatio(float value) = 0;

        virtual ~ICameraStrategy() = default;
    };

}

#endif // TENGINE_ICAMERASTRATEGY_H