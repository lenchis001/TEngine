#include <stdexcept>

#include "SceneService.h"

#include "CameraStrategies/CameraStrategyBase.h"
#include "CameraStrategies/FpsCameraStrategy.h"
#include "CameraStrategies/ViewerCameraStrategy.h"
#include "RenderingStrategies/Primitives/CubeRenderingStrategy.h"
#include "RenderingStrategies/RenderingStrategyBase.h"
#include "RenderingStrategies/RenderingOptimizationDecorator.h"
#include "RenderingStrategies/Meshes/MeshRenderingStrategy.h"
#include "RenderingStrategies/PhysicsRenderingDecorator.h"
#include "RenderingStrategies/Solid/SolidboxRenderingStrategy.h"
#include "RenderingStrategies/Empty/EmptyRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Empty;

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
	  _root(std::make_shared<EmptyRenderingStrategy>()),
	  _buildinCameraTrackingStrategies(buildinCameraTrackingStrategies)
{
}

void SceneService::initialize()
{
	_physicsService->initialize();
}

void SceneService::deinitialize()
{
	_root->removeAllChildren();
}

void SceneService::render(double time)
{
	_physicsService->update(time);

	if (_activeCamera)
	{
		_lightServices->update();
		_activeCamera->render(time);

		_root->render(_activeCamera);
	}
}

std::shared_ptr<IRenderingStrategy> SceneService::addPrimitive(
	PrimitiveTypes type,
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent,
	PhysicsFlags physicsFlags)
{
	std::shared_ptr<IRenderingStrategy> strategy = std::make_shared<CubeRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_textureService,
		texturePath);

	if (physicsFlags != PhysicsFlags::NONE)
	{
		strategy = std::make_shared<PhysicsRenderingDecorator>(_physicsService, strategy, physicsFlags);
	}

	auto decoratedCubeRenderingStrategy = std::make_shared<RenderingOptimizationDecorator>(strategy);
	(parent ? parent : _root)->addChild(decoratedCubeRenderingStrategy);

	return decoratedCubeRenderingStrategy;
}

std::shared_ptr<IRenderingStrategy> SceneService::addMesh(
	std::string path,
	std::shared_ptr<IRenderingStrategy> parent,
	PhysicsFlags physicsFlags)
{
	std::shared_ptr<IRenderingStrategy> strategy = std::make_shared<MeshRenderingStrategy>(_meshService, _lightServices, path);

	if (physicsFlags != PhysicsFlags::NONE)
	{
		strategy = std::make_shared<PhysicsRenderingDecorator>(_physicsService, strategy, physicsFlags);
	}

	auto decoratedMeshRenderingStrategy = std::make_shared<RenderingOptimizationDecorator>(strategy);
	(parent ? parent : _root)->addChild(decoratedMeshRenderingStrategy);

	return decoratedMeshRenderingStrategy;
}

std::shared_ptr<IRenderingStrategy> SceneService::addSolidbox(
	std::shared_ptr<IRenderingStrategy> parent)
{
	std::shared_ptr<IRenderingStrategy> strategy = std::make_shared<SolidboxRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_textureService,
		"./DemoResources/texture2.bmp");

	strategy = std::make_shared<PhysicsRenderingDecorator>(_physicsService, strategy, PhysicsFlags::STATIC);

	auto decoratedSolidboxRenderingStrategy = std::make_shared<RenderingOptimizationDecorator>(strategy);
	(parent ? parent : _root)->addChild(decoratedSolidboxRenderingStrategy);

	return decoratedSolidboxRenderingStrategy;
}

std::shared_ptr<IRenderingStrategy> SceneService::addEmpty(
	std::shared_ptr<IRenderingStrategy> parent)
{
	std::shared_ptr<IRenderingStrategy> strategy = std::make_shared<EmptyRenderingStrategy>();

	(parent ? parent : _root)->addChild(strategy);

	return strategy;
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
	case BuildinCameraTypes::VIEWER:
		setActiveCamera(std::make_shared<ViewerCameraStrategy>(_eventService, 45.0f, windowSize, 0.1f, 100.f, Vector3df(4, 3, 3)));
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

std::shared_ptr<IRenderingStrategy> SceneService::getRoot()
{
	return _root;
}

Vector2di SceneService::_getWindowSize() const
{
	return Vector2di(1280, 720);
}