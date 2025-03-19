#include "LightService.h"

#include <algorithm>

#include "Components/Graphics/Rendering/Scene/Models/Lights/PointLight.h"
#include "Components/Graphics/Models/Box.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

LightService::LightService()
{
}

LightService::~LightService()
{
}

void LightService::update()
{
}

void LightService::updateTrackingObjectState(std::shared_ptr<ILightRenderingStrategy> strategy)
{
}

void LightService::stopTracking(int id)
{
}

std::shared_ptr<IPointLight> LightService::addPointLight(const Vector3df &position, const Vector3df &diffuseColor, float radius)
{
	auto pointLight =
		std::make_shared<PointLight>(
			position,
			diffuseColor,
			radius,
			std::bind(&LightService::_onPointLightUpdated, this));

	_pointLights.push_back(pointLight);

	return pointLight;
}

void LightService::removePointLight(const std::shared_ptr<IPointLight> light)
{
	_pointLights.remove(light);
}

void LightService::_onPointLightUpdated()
{
	// tracking objects clean required?
	_processingLock.lock();
	_trakingStrategies.remove_if([](auto strategy)
								 { return strategy.expired(); });

	auto lockedStrategies = std::list<std::shared_ptr<ILightRenderingStrategy>>(_trakingStrategies.size());

	std::transform(_trakingStrategies.begin(), _trakingStrategies.end(), lockedStrategies.begin(), [](auto strategy)
				   { return strategy.lock(); });
	_processingLock.unlock();

	for (auto &strategy : lockedStrategies)
	{
		_processingLock.lock();
		auto position = strategy->getAbsolutePosition();
		auto size = strategy->getSize();
		_processingLock.unlock();

		auto strategyBox = Box3df(position, size);

		std::vector<std::shared_ptr<IPointLight>> visiblePointLights;
		std::copy_if(
			_pointLights.begin(),
			_pointLights.end(),
			std::back_inserter(visiblePointLights),
			[&strategyBox](const std::shared_ptr<IPointLight> &light)
			{
				auto lightPosition = light->getPosition();
				auto lightRadius = light->getRadius();
				auto lightBox = Box3df(lightPosition, Vector3df(lightRadius, lightRadius, lightRadius));

				return strategyBox.overlaps(lightBox);
			});

		_processingLock.lock();
		strategy->updatePointLights(std::move(visiblePointLights));
		_processingLock.unlock();
	}
}
