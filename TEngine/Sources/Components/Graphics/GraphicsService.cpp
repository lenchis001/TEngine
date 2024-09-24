#include "GraphicsService.h"

#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"

using namespace TEngine::Components::Graphics::Services;

using namespace TEngine::Components::Graphics::CameraTracking;

GraphicsService::GraphicsService(
	std::shared_ptr<IRenderingService> renderingService,
	std::shared_ptr<IMeshLoadingService> meshLoadingService,
	std::shared_ptr<ITexturesService> texturesService,
	std::shared_ptr<IAudioService> audioService)
	: _renderingService(renderingService),
	  _meshLoadingService(meshLoadingService),
	  _texturesService(texturesService)
{
	_cameraTrackingStrategies.push_back(std::make_shared<ListenerCameraTrackingStrategy>(audioService));
}

void GraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
	_meshLoadingService->initialize();
	_texturesService->initialize();
	_renderingService->initialize(parameters->getRenderingParameters());
}

bool GraphicsService::isShutdownRequested() const
{
	return _renderingService->isShutdownRequested();
}

double GraphicsService::getTime() const
{
	return _renderingService->getTime();
}

std::shared_ptr<IRenderingStrategy> GraphicsService::addPrimitive(
	PrimitiveTypes type, 
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	return _renderingService->addToRendering(type, texturePath, parent);
}

std::shared_ptr<IRenderingStrategy> GraphicsService::addMesh(
	std::string path,
	std::shared_ptr<IRenderingStrategy> parent)
{
	return _renderingService->addMeshToRendering(path, parent);
}

std::shared_ptr<ICameraStrategy> GraphicsService::setActiveCamera(BuildinCameraTypes cameraType)
{
	auto camera = _renderingService->setActiveCamera(cameraType);

	for (auto &trackingStrategy : _cameraTrackingStrategies)
	{
		camera->addTrackingStrategy(trackingStrategy);
	}

	return camera;
}

void GraphicsService::setActiveCamera(std::shared_ptr<ICameraStrategy> camera)
{
	_renderingService->setActiveCamera(camera);

	for (auto &trackingStrategy : _cameraTrackingStrategies)
	{
		camera->addTrackingStrategy(trackingStrategy);
	}
}

std::shared_ptr<IWindowRenderingStrategy> GraphicsService::addWindow()
{
	return _renderingService->addWindow();
}