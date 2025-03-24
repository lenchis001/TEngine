#include "LightService.h"

#include <algorithm>

#include "Components/Graphics/Rendering/Scene/Models/Lights/PointLight.h"
#include "Components/Graphics/Rendering/Scene/Models/Lights/Shader/ShaderPointLight.h"
#include "Components/Graphics/Rendering/Scene/Models/Lights/Shader/ShaderPointLight.h"
#include "Components/Graphics/Models/Box.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

using namespace TEngine::Components::Graphics::Rendering::Scene::Models::Lights::Shader;

LightService::LightService()
{
}

LightService::~LightService()
{
}

void LightService::update()
{
}

void LightService::addToTrack(std::shared_ptr<ILightRenderingStrategy> strategy)
{
	_processingLock.lock();
	_trakingStrategies.push_back(strategy);
	_processingLock.unlock();

	_onPointLightUpdated();
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

	_onPointLightUpdated();

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

		std::vector<ShaderPointLight> visiblePointLights;
		for (auto &light : _pointLights)
		{
			auto lightPosition = light->getPosition();
			auto lightRadius = light->getRadius();
			auto lightBox = Box3df(lightPosition, Vector3df(lightRadius, lightRadius, lightRadius));

			if (strategyBox.overlaps(lightBox))
			{
				auto shaderLight = ShaderPointLight();
				shaderLight.position[0] = lightPosition.getX();
				shaderLight.position[1] = lightPosition.getY();
				shaderLight.position[2] = lightPosition.getZ();

				auto color = light->getDiffuseColor();
				shaderLight.color[0] = color.getX();
				shaderLight.color[1] = color.getY();
				shaderLight.color[2] = color.getZ();

				shaderLight.intensity = light->getRadius();

				visiblePointLights.push_back(shaderLight);
			}
		}

		_processingLock.lock();
		strategy->updatePointLights(std::move(visiblePointLights));
		_processingLock.unlock();
	}
}
