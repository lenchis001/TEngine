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
#include "Components/Graphics/Rendering/Services/Meshes/MeshService.h"
#include "Components/Audio/Services/Readers/VorbisOggReader.h"
#include "Components/Audio/Services/AudioService.h"

#include "Components/Events/Services/EventService.h"

using namespace TEngine;
using namespace TEngine::Components::Graphics::Services;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Audio::Services::Readers;
using namespace TEngine::Components::Audio::Services;

using namespace TEngine::Components::Events::Services;

std::shared_ptr<IEngine> TEngine::createEngine()
{
    auto eventsService = std::make_shared<EventService>();

    auto vorbisOggReader = std::make_shared<VorbisOggReader>();
    auto audioService = std::make_shared<AudioService>(vorbisOggReader);

    auto imageLoadingService = std::make_shared<ImageLoadingService>();
    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto shadersService = std::make_shared<ShadersService>();
    auto bufferCacheService = std::make_shared<BuffersService>();
    auto texturesService = std::make_shared<TexturesService>(imageLoadingService);
    auto meshService = std::make_shared<MeshService>(meshLoadingService, bufferCacheService, shadersService);

    auto renderingService = std::make_shared<RenderingService>(eventsService, shadersService, bufferCacheService, texturesService, meshService);

    auto graphicsService = std::make_shared<GraphicsService>(renderingService, meshLoadingService, texturesService, audioService);

    return std::make_shared<Engine>(graphicsService, eventsService, audioService);
}