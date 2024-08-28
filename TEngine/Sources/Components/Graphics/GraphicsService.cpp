#include "GraphicsService.h"

using namespace TEngine::Components::Graphics::Services;

GraphicsService::GraphicsService(
	std::shared_ptr<IRenderingService> renderingService,
	std::shared_ptr<IMeshLoadingService> meshLoadingService,
	std::shared_ptr<ITexturesService> texturesService)
	: _renderingService(renderingService),
	  _meshLoadingService(meshLoadingService),
	  _texturesService(texturesService)
{
}

void GraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
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

void GraphicsService::render()
{
	_renderingService->render();
}

std::future<DataActionResult<ErrorCodes, IRenderingStrategy>> GraphicsService::loadMesh(const std::wstring &path)
{
	return std::async(std::launch::async, [path]() -> DataActionResult<ErrorCodes, IRenderingStrategy>
					  { throw ""; });
}

std::shared_ptr<IRenderingStrategy> GraphicsService::addPrimitive(
	PrimitiveTypes type, 
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto primitive = _renderingService->addToRendering(type, texturePath, parent);

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