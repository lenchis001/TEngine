#include "LightService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

LightService::LightService()
{
}

LightService::~LightService()
{
	_threadPool.join();
}

void LightService::update()
{

}

void LightService::updateTrackingObjectState(int id, const Vector3df& position, const Vector3df& size)
{
	_trackingObjects[id] = Box3df(position, size);
}

std::shared_ptr<IPointLight> TEngine::Components::Graphics::Rendering::Scene::Lights::LightService::addPointLight(const Vector3df& position, const Vector3df& diffuseColor, float radius)
{
	return nullptr;// std::make_shared<PointLight>(position, diffuseColor, radius, [this]() {});
}
