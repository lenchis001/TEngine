#include "stdexcept"

#include "GLFW/glfw3.h"

#include "SceneService.h"

#include "CameraStrategies/CameraStrategyBase.h"
#include "CameraStrategies/FpsCameraStrategy.h"
#include "RenderingStrategies/Primitives/CubeRenderingStrategy.h"
#include "RenderingStrategies/RenderingStrategyBase.h"
#include "RenderingStrategies/RenderingOptimizationDecorator.h"
#include "RenderingStrategies/Meshes/MeshRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Meshes;

SceneService::SceneService(
	std::shared_ptr<IEventService> eventService,
	std::shared_ptr<IShadersService> shadersService,
	std::shared_ptr<IBuffersService> bufferCacheService,
	std::shared_ptr<ITexturesService> textureService,
	std::shared_ptr<IMeshService> meshService,
	std::shared_ptr<ILightServices> lightServices,
	std::shared_ptr<IPhysicsService> physicsService,
	std::vector<std::shared_ptr<ICameraTrackingStrategy>> buildinCameraTrackingStrategies)
	: _eventService(eventService),
	  _shadersService(shadersService),
	  _bufferCacheService(bufferCacheService),
	  _textureService(textureService),
	  _meshService(meshService),
	  _lightServices(lightServices),
	  _physicsService(physicsService),
	  _activeCamera(nullptr),
	  _root(std::make_shared<RenderingStrategyBase>()),
	  _buildinCameraTrackingStrategies(buildinCameraTrackingStrategies)
{
}

void SceneService::initialize()
{
	_physicsService->initialize();
}

void SceneService::render(double time)
{
	_lightServices->update();
	_physicsService->update(time);

	if (_activeCamera)
	{
		_activeCamera->render(time);

		_root->render(_activeCamera);
	}
}

std::shared_ptr<IRenderingStrategy> SceneService::addToRendering(
	PrimitiveTypes type,
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto cubeRenderingStrategy = std::make_shared<CubeRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_textureService,
		texturePath);

	auto decoratedCubeRenderingStrategy = std::make_shared<RenderingOptimizationDecorator>(cubeRenderingStrategy);
	(parent ? parent : _root)->addChild(decoratedCubeRenderingStrategy);

	return decoratedCubeRenderingStrategy;
}

std::shared_ptr<IRenderingStrategy> SceneService::addMeshToRendering(
	std::string meshPath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto meshRenderingStrategy = std::make_shared<MeshRenderingStrategy>(_meshService, _lightServices, meshPath);

	auto decoratedMeshRenderingStrategy = std::make_shared<RenderingOptimizationDecorator>(meshRenderingStrategy);
	(parent ? parent : _root)->addChild(decoratedMeshRenderingStrategy);

	return decoratedMeshRenderingStrategy;
}

std::shared_ptr<ICameraStrategy> SceneService::setActiveCamera(BuildinCameraTypes cameraType)
{
	auto windowSize = _getWindowSize();

	switch (cameraType)
	{
	case BuildinCameraTypes::BASE:
		setActiveCamera(std::make_shared<CameraStrategyBase>(45.0f, windowSize, 0.1f, 100.f, Vector3df(4, 3, 3), Vector3df(0, 0, 0)));
		break;
	case BuildinCameraTypes::FPS:
		setActiveCamera(std::make_shared<FpsCameraStrategy>(_eventService, 45.0f, windowSize, 0.1f, 100.f, Vector3df(4, 3, 3)));
		break;
	default:
		_activeCamera = nullptr;
		break;
	}

	return _activeCamera;
}

std::shared_ptr<ICameraStrategy> SceneService::getActiveCamera()
{
	return _activeCamera;
}

void SceneService::setActiveCamera(std::shared_ptr<ICameraStrategy> camera)
{
	_activeCamera = camera;

	for (auto &trackingStrategy : _buildinCameraTrackingStrategies)
	{
		camera->addTrackingStrategy(trackingStrategy);
	}
}

Vector2di SceneService::_getWindowSize() const
{
	int width, height;
	glfwGetWindowSize(glfwGetCurrentContext(), &width, &height);

	return Vector2di(width, height);
}