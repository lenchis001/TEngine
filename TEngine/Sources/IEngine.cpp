#include "IEngine.h"

#include "memory"

#include "Engine.h"

#include "Components/Graphics/GraphicsService.h"
#include "Components/Graphics/Rendering/Services/RenderingService.h"
#include "Components/Graphics/MeshLoading/Services/MeshLoadingService.h"
#include "Components/Graphics/Rendering/Services/Shaders/ShadersService.h"
#include "Components/Graphics/ImageLoading/Services/ImageLoadingService.h"
#include "Components/Graphics/Rendering/Services/Buffers/BuffersService.h"

using namespace TEngine;
using namespace TEngine::Components::Graphics::Services;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Services;

std::shared_ptr<IEngine> TEngine::createEngine()
{
    auto shadersService = std::make_shared<ShadersService>();
    auto bufferCacheService = std::make_shared<BuffersService>();

    auto renderingService = std::make_shared<RenderingService>(shadersService, bufferCacheService);
    
    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto imageLoadingService = std::make_shared<ImageLoadingService>();

    auto graphicsService = std::make_shared<GraphicsService>(renderingService, meshLoadingService, imageLoadingService);

    return std::make_shared<Engine>(graphicsService);
}