#include "GraphicsService.h"

#include "Components/Graphics/Rendering/Models/RenderableObjects/RenderableObjectBase.h"

using namespace TEngine::Components::Graphics::Services;

GraphicsService::GraphicsService(std::shared_ptr<IRenderingService> renderingService, std::shared_ptr<IMeshLoadingService> meshLoadingService)
	: _renderingService(renderingService),
	  _meshLoadingService(meshLoadingService)
{
}

void GraphicsService::initialize(std::shared_ptr<IGraphicsParameters> parameters)
{
	_renderingService->initialize(parameters->getRenderingParameters());
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

std::shared_ptr<IRenderableObject> GraphicsService::addPrimitive(PrimitiveTypes type)
{
	auto primitive = std::make_shared<RenderableObjectBase>();

	_renderingService->addToRendering(primitive, type);

	return primitive;
}
