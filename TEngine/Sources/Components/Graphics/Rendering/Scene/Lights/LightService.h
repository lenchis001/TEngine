#ifndef TENGINE_LIGHTSERVICE_H
#define TENGINE_LIGHTSERVICE_H

#include <map>

#include <boost/asio.hpp>

#include "Components/Graphics/Models/Box.h"

#include "ILightServices.h"

#include "Mixins/ThreadSafeExecutionAware.h"

using namespace boost::asio;

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Models::Lights;
using namespace TEngine::Mixins;

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Scene::Lights
{
    class LightService : public ILightServices, private ThreadSafeExecutionAware
    {
    public:
        LightService();
		~LightService() override;

        void update() override;

        void updateTrackingObjectState(int id, const Vector3df& position, const Vector3df& size) override;

		std::shared_ptr<IPointLight> addPointLight(const Vector3df& position, const Vector3df& diffuseColor, float radius) override;

    private:
        std::map<int, Box3df> _trackingObjects;

		thread_pool _threadPool;
    };
}

#endif // TENGINE_LIGHTSERVICE_H