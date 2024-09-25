#ifndef TENGINE_LIGHTSERVICE_H
#define TENGINE_LIGHTSERVICE_H

#include "ILightServices.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Lights;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::Lights
{
    class LightService : public ILightServices
    {
    public:
        LightService();

        void update() override;

        const std::shared_ptr<IPointLight> getPointLight() const override;

    private:
        std::shared_ptr<IPointLight> _pointLight;
    };
}

#endif // TENGINE_LIGHTSERVICE_H