#include "GraphicsService.h"

using namespace TEngine::Components::Graphics::Services;

GraphicsService::GraphicsService(std::shared_ptr<IRenderingService> renderingService, std::shared_ptr<IMeshLoadingService> meshLoadingService)
	: _renderingService(renderingService),
	  _meshLoadingService(meshLoadingService)
{
}

void GraphicsService::initialize(GraphicsParameters& parameters)
{
	_renderingService->initialize(parameters.getRenderingParameters());
}

void GraphicsService::render()
{
	_renderingService->render();
}

std::future<MeshLoadingDataActionResult> GraphicsService::loadMesh(const std::wstring &path)
{
	return std::async(std::launch::async, [path]() -> MeshLoadingDataActionResult
					  { throw ""; });
}
