#ifndef TENGINE_POINTLIGHT_H
#define TENGINE_POINTLIGHT_H

#include "IPointLight.h"

#include <memory>

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Scene::Models::Lights
{
    typedef std::function<void(std::shared_ptr<IPointLight>)> PointLightUpdatedCallback;

    class PointLight : public IPointLight, public std::enable_shared_from_this<IPointLight>
    {
    public:
        PointLight(const Vector3df &position, const Vector3df &diffuseColor, float radius, PointLightUpdatedCallback lightUpdateRequiredCallback);

        void setPosition(const Vector3df &position) override;
        const Vector3df& getPosition() const override;

        const Vector3df& getDiffuseColor() const override;

		float getRadius() const override;
		void setRadius(float radius) override;

    private:
        Vector3df _position;
        Vector3df _diffuseColor;
        float _radius;

        PointLightUpdatedCallback _lightUpdateRequiredCallback;
    };
}

#endif // TENGINE_POINTLIGHT_H