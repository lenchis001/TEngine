#include "IEngine.h"

#include "memory"

#include "Engine.h"

#include "Components/Graphics/GraphicsService.h"
#include "Components/Graphics/Rendering/Services/RenderingService.h"
#include "Components/Graphics/MeshLoading/Services/MeshLoadingService.h"
#include "Components/Graphics/Rendering/Services/Shaders/ShadersService.h"
#include "Components/Graphics/ImageLoading/Services/ImageLoadingService.h"
#include "Components/Graphics/Rendering/Services/Buffers/BuffersService.h"
#include "Components/Graphics/Rendering/Services/Textures/TexturesService.h"
#include "Components/Graphics/Rendering/Services/Optimization/BigWorldService.h"

using namespace TEngine;
using namespace TEngine::Components::Graphics::Services;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Graphics::Rendering::Services::Optimization;

std::shared_ptr<IEngine> TEngine::createEngine()
{
    auto imageLoadingService = std::make_shared<ImageLoadingService>();

    auto shadersService = std::make_shared<ShadersService>();
    auto bufferCacheService = std::make_shared<BuffersService>();
    auto texturesService = std::make_shared<TexturesService>(imageLoadingService);
    auto bigWorldService = std::make_shared<BigWorldService>();

    auto renderingService = std::make_shared<RenderingService>(shadersService, bufferCacheService, texturesService, bigWorldService);

    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto graphicsService = std::make_shared<GraphicsService>(renderingService, meshLoadingService, texturesService);

    return std::make_shared<Engine>(graphicsService);
}