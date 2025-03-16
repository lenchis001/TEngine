#ifndef TENGINE_LIGHTSERVICE_H
#define TENGINE_LIGHTSERVICE_H

#include <map>
#include <list>
#include <memory>

#include "ILightService.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Light/ILightRenderingStrategy.h"

#include "Mixins/SpinLock.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Lights;
using namespace TEngine::Mixins;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Light;

namespace TEngine::Components::Graphics::Rendering::Scene::Lights
{
    class LightService : public ILightService
    {
    public:
        LightService();
		~LightService() override;

        void update() override;

        void updateTrackingObjectState(std::shared_ptr<ILightRenderingStrategy> strategy) override;

        void stopTracking(int id) override;

		std::shared_ptr<IPointLight> addPointLight(const Vector3df& position, const Vector3df& diffuseColor, float radius) override;
        void removePointLight(const std::shared_ptr<IPointLight> light) override;

    private:
        void _onPointLightUpdated();

        SpinLock _processingLock;

        std::list<std::shared_ptr<IPointLight>> _pointLights;
        std::list<std::weak_ptr<ILightRenderingStrategy>> _trakingStrategies;
    };
}

#endif // TENGINE_LIGHTSERVICE_H