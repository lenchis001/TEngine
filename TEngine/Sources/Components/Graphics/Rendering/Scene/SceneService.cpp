#include <stdexcept>

#include "SceneService.h"

#include "CameraStrategies/CameraStrategyBase.h"
#include "CameraStrategies/FpsCameraStrategy.h"
#include "CameraStrategies/ViewerCameraStrategy.h"
#include "RenderingStrategies/Primitives/CubeRenderingStrategy.h"
#include "RenderingStrategies/RenderingStrategyBase.h"
#include "RenderingStrategies/Meshes/MeshRenderingStrategy.h"
#include "RenderingStrategies/Solid/SolidboxRenderingStrategy.h"
#include "RenderingStrategies/Empty/EmptyRenderingStrategy.h"
#include "RenderingStrategies/Sky/SkySphereRenderingStrategy.h"
#include "Sequence/IRenderingSequenceService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Empty;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky;
using namespace TEngine::Components::Graphics::Rendering::Scene::Sequence;

SceneService::SceneService(
	std::shared_ptr<IEventService> eventService,
	std::shared_ptr<IShadersService> shadersService,
	std::shared_ptr<IBuffersService> bufferCacheService,
	std::shared_ptr<ITexturesService> textureService,
	std::shared_ptr<IMeshService> meshService,
	std::shared_ptr<ILightService> lightServices,
	std::shared_ptr<IPhysicsService> physicsService,
	std::shared_ptr<IRenderingSequenceService> renderingSequenceService,
	std::vector<std::shared_ptr<ICameraTrackingStrategy>> buildinCameraTrackingStrategies)
	: _eventService(eventService),
	  _shadersService(shadersService),
	  _bufferCacheService(bufferCacheService),
	  _textureService(textureService),
	  _meshService(meshService),
	  _lightServices(lightServices),
	  _physicsService(physicsService),
	  _renderingSequenceService(renderingSequenceService),
	  _activeCamera(nullptr),
	  _root(std::make_shared<EmptyRenderingStrategy>(std::bind(&SceneService::_updateRenderingSequence, this))),
	  _buildinCameraTrackingStrategies(buildinCameraTrackingStrategies),
	  _lastOptimizedPosition(Vector3df(0, 0, 0)),
	  _sequenceUpdateThreshold(10.0f)
{
}

void SceneService::initialize(std::shared_ptr<ISceneParameters> parameters)
{
	_sequenceUpdateThreshold = parameters->getSequenceUpdateThreshold();

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

		_updateRenderingSequenceIfNecessary();

		_root->update(_activeCamera);

		for (const auto &strategy : _renderingSequence)
		{
			strategy->render(_activeCamera);
		}
	}
}

std::shared_ptr<ICubeRenderingStrategy> SceneService::addCube(
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent,
	PhysicsFlags physicsFlags)
{
	std::shared_ptr<ICubeRenderingStrategy> strategy = std::make_shared<CubeRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_textureService,
		_physicsService,
		std::bind(&SceneService::_updateRenderingSequence, this));

	if (!texturePath.empty())
	{
		strategy->setTexture(texturePath);
	}
	strategy->setPhysicsFlags(physicsFlags);

	(parent ? parent : _root)->addChild(strategy);

	_updateRenderingSequence();

	return strategy;
}

std::shared_ptr<IMeshRenderingStrategy> SceneService::addMesh(
	std::string path,
	std::shared_ptr<IRenderingStrategy> parent,
	PhysicsFlags physicsFlags)
{
	std::shared_ptr<IMeshRenderingStrategy> strategy = std::make_shared<MeshRenderingStrategy>(
		_meshService,
		_lightServices,
		_physicsService,
		_textureService,
		std::bind(&SceneService::_updateRenderingSequence, this),
		path);

	strategy->setPhysicsFlags(physicsFlags);

	(parent ? parent : _root)->addChild(strategy);

	_updateRenderingSequence();

	return strategy;
}

std::shared_ptr<ISolidboxRenderingStrategy> SceneService::addSolidbox(
	std::shared_ptr<IRenderingStrategy> parent)
{
	std::shared_ptr<ISolidboxRenderingStrategy> strategy = std::make_shared<SolidboxRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_physicsService,
		std::bind(&SceneService::_updateRenderingSequence, this));

	(parent ? parent : _root)->addChild(strategy);

	strategy->setPhysicsFlags(PhysicsFlags::STATIC);

	_updateRenderingSequence();

	return strategy;
}

std::shared_ptr<IRenderingStrategy> SceneService::addEmpty(
	std::shared_ptr<IRenderingStrategy> parent)
{
	std::shared_ptr<IRenderingStrategy> strategy = std::make_shared<EmptyRenderingStrategy>(std::bind(&SceneService::_updateRenderingSequence, this));

	(parent ? parent : _root)->addChild(strategy);

	_updateRenderingSequence();

	return strategy;
}

std::shared_ptr<IRenderingStrategy> SceneService::addSkySphere(
	std::shared_ptr<IRenderingStrategy> parent)
{
	std::shared_ptr<SkySphereRenderingStrategy> strategy = std::make_shared<SkySphereRenderingStrategy>(
		_shadersService,
		_bufferCacheService,
		_textureService,
		std::bind(&SceneService::_updateRenderingSequence, this));

	// todo: remoove after test
	strategy->setTexture(
		"./DemoResources/skybox/right.bmp",
		"./DemoResources/skybox/left.bmp",
		"./DemoResources/skybox/top.bmp",
		"./DemoResources/skybox/bottom.bmp",
		"./DemoResources/skybox/front.bmp",
		"./DemoResources/skybox/back.bmp");
	strategy->setCube(20.0f);
	strategy->setScale(Vector3df(100.0f, 100.0f, 100.0f));

	(parent ? parent : _root)->addChild(strategy);

	_updateRenderingSequence();

	return strategy;
}

std::shared_ptr<ICameraStrategy> SceneService::setActiveCamera(BuildinCameraTypes cameraType)
{
	auto windowSize = _getWindowSize();

	switch (cameraType)
	{
	case BuildinCameraTypes::BASE:
		setActiveCamera(std::make_shared<CameraStrategyBase>(45.0f, windowSize, 0.1f, 200.f, Vector3df(4, 3, 3), Vector3df(0, 0, 0)));
		break;
	case BuildinCameraTypes::FPS:
		setActiveCamera(std::make_shared<FpsCameraStrategy>(_eventService, 45.0f, windowSize, 0.1f, 200.f, Vector3df(4, 3, 3)));
		break;
	case BuildinCameraTypes::VIEWER:
		setActiveCamera(std::make_shared<ViewerCameraStrategy>(_eventService, 45.0f, windowSize, 0.1f, 200.f, Vector3df(4, 3, 3)));
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

void SceneService::_updateRenderingSequenceIfNecessary()
{
	const auto &cameraPosition = _activeCamera->getPosition();

	if (_lastOptimizedPosition.distance(cameraPosition) > _sequenceUpdateThreshold)
	{
		_updateRenderingSequence();
	}
}

void SceneService::_updateRenderingSequence()
{
	const auto &cameraPosition = _activeCamera->getPosition();

	_renderingSequence = _renderingSequenceService->generateSequence(_root, cameraPosition);

	_lastOptimizedPosition = cameraPosition;
}