#include "IEngine.h"

#include "memory"

#include "Engine.h"

#include "Components/Graphics/GraphicsService.h"
#include "Components/Graphics/Rendering/Services/RenderingService.h"
#include "Components/Graphics/MeshLoading/Services/MeshLoadingService.h"
#include "Components/Graphics/Rendering/Services/Shaders/ShadersService.h"
#include "Components/Graphics/ImageLoading/Services/ImageLoadingService.h"

using namespace TEngine;
using namespace TEngine::Components::Graphics::Services;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Services;

std::shared_ptr<IEngine> TEngine::createEngine()
{
    auto shadersService = std::make_shared<ShadersService>();

    auto renderingService = std::make_shared<RenderingService>(shadersService);

    auto imageLoadingService = std::make_shared<ImageLoadingService>();
    imageLoadingService->initialize();
    auto result = imageLoadingService->load("D:/480-360-sample.bmp");

    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto graphicsService = std::make_shared<GraphicsService>(renderingService, meshLoadingService);

    return std::make_shared<Engine>(graphicsService);
}