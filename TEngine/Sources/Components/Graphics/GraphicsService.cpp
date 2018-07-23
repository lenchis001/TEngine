#include "GraphicsService.h"

using namespace TEngine::Components::Graphics::Services;

void GraphicsService::render()
{
	_renderingService->render();
}

std::future<MeshLoadingDataActionResult> GraphicsService::loadMesh(const std::wstring& path)
{
	return std::async(std::launch::async, [path]() -> MeshLoadingDataActionResult
		{ throw ""; });
}
