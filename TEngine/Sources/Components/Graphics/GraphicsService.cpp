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

std::shared_ptr<IRenderingStrategy> GraphicsService::loadMesh(const std::string &path)
{
	return nullptr;
}

std::shared_ptr<IRenderingStrategy> GraphicsService::addPrimitive(
	PrimitiveTypes type, 
	std::string texturePath,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto primitive = _renderingService->addToRendering(type, texturePath, parent);

	return primitive;
}

std::shared_ptr<IRenderingStrategy> GraphicsService::addMesh(
	std::string path,
	std::shared_ptr<IRenderingStrategy> parent)
{
	auto mesh = _renderingService->addMeshToRendering(path, parent);

	return mesh;
}

std::shared_ptr<ICameraStrategy> GraphicsService::setActiveCamera(BuildinCameraTypes cameraType)
{
	return _renderingService->setActiveCamera(cameraType);
}

void GraphicsService::setActiveCamera(std::shared_ptr<ICameraStrategy> camera)
{
	_renderingService->setActiveCamera(camera);
}