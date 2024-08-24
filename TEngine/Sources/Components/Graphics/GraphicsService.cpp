#include "GraphicsService.h"

using namespace TEngine::Components::Graphics::Services;

GraphicsService::GraphicsService(
	std::shared_ptr<IRenderingService> renderingService,
	std::shared_ptr<IMeshLoadingService> meshLoadingService,
	std::shared_ptr<IImageLoadingService> imageLoadingService)
	: _renderingService(renderingService),
	  _meshLoadingService(meshLoadingService),
	  _imageLoadingService(imageLoadingService)
{
}

void GraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
	_imageLoadingService->initialize();
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

void GraphicsService::render()
{
	_renderingService->render();
}

std::future<DataActionResult<ErrorCodes, IMeshRenderableObject>> GraphicsService::loadMesh(const std::wstring &path)
{
	return std::async(std::launch::async, [path]() -> DataActionResult<ErrorCodes, IMeshRenderableObject>
					  { throw ""; });
}

std::shared_ptr<IRenderableObject> GraphicsService::addPrimitive(
	PrimitiveTypes type, 
	std::string texturePath,
	std::shared_ptr<IRenderableObject> parent)
{
	auto image = _imageLoadingService->load(texturePath);

	auto primitive = _renderingService->addToRendering(type, image, parent);

	return primitive;
}

std::shared_ptr<ICameraStrategy> GraphicsService::setActiveCamera(BuildinCameraTypes cameraType)
{
	return _renderingService->setActiveCamera(cameraType);
}

void GraphicsService::setActiveCamera(std::shared_ptr<ICameraStrategy> camera)
{
	_renderingService->setActiveCamera(camera);
}