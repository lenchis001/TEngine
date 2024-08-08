#include "IEngine.h"

#include "memory"

#include "Engine.h"

#include "Components/Graphics/GraphicsService.h"
#include "Components/Graphics/Services/Rendering/RenderingService.h"
#include "Components/Graphics/Services/MeshLoading/MeshLoadingService.h"

using namespace TEngine;
using namespace TEngine::Components::Graphics::Services;
using namespace TEngine::Components::Graphics::Services::Rendering;
using namespace TEngine::Components::Graphics::Services::MeshLoading;

std::shared_ptr<IEngine> TEngine::createEngine()
{
    auto renderingService = std::make_shared<RenderingService>();
    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto graphicsService = std::make_shared<GraphicsService>(renderingService, meshLoadingService);

    return std::make_shared<Engine>(graphicsService);
}