#ifndef TENGINE_POINTLIGHT_H
#define TENGINE_POINTLIGHT_H

#include "IPointLight.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Models::Lights
{
    class PointLight : public IPointLight
    {
    public:
        PointLight(const Vector3df &position, const Vector3df &diffuseColor);

        void setPosition(const Vector3df &position) override;
        const Vector3df& getPosition() const override;

        const Vector3df& getDiffuseColor() const override;

    private:
        Vector3df _position;
        Vector3df _diffuseColor;
    };
}

#endif // TENGINE_POINTLIGHT_H