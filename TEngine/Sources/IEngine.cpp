#include "IEngine.h"

#include <memory>

#include "Engine.h"

#include "Components/Graphics/GlfwGraphicsService.h"
#include "Components/Graphics/Rendering/Scene/SceneService.h"
#include "Components/Graphics/MeshLoading/Services/MeshLoadingService.h"
#include "Components/Graphics/Rendering/Scene/Shaders/ShadersService.h"
#include "Components/Graphics/ImageLoading/Services/ImageLoadingService.h"
#include "Components/Graphics/Rendering/Scene/Buffers/BuffersService.h"
#include "Components/Graphics/Rendering/Textures/TexturesService.h"
#include "Components/Graphics/Rendering/Scene/Meshes/MeshService.h"
#include "Components/Graphics/Rendering/Scene/Physics/PhysicsService.h"
#include "Components/Graphics/Rendering/Scene/Physics/EmptyPhysicsService.h"
#include "Components/Graphics/Rendering/Scene/Sequence/RenderingSequenceService.h"
#include "Components/Graphics/Rendering/Gui/GlfwGuiService.h"
#include "Components/Graphics/Rendering/Gui/Win32GuiService.h"
#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"
#include "Components/Audio/Services/Readers/VorbisOggReader.h"
#include "Components/Audio/Services/AudioService.h"
#include "Components/Events/Services/GlfwEventService.h"

#include "Components/State/Serialization/SerializationService.h"
#include "Components/Graphics/Rendering/Scene/State/Serialization/Meshes/MeshRenderingStrategySerializer.h"
#include "Components/Graphics/Rendering/Scene/State/Serialization/Solid/SolidboxRenderingStrategySerializer.h"
#include "Components/Graphics/Rendering/Scene/State/Serialization/Primitives/CubeRenderingStrategySerializer.h"
#include "Components/Graphics/Rendering/Scene/State/Serialization/Empty/EmptyRenderingStrategySerializer.h"
#include "Components/State/Deserialization/DeserializationService.h"
#include "Components/Graphics/Rendering/Scene/State/Deserialization/Empty/EmptyRenderingStrategyDeserializer.h"
#include "Components/Graphics/Rendering/Scene/State/Deserialization/Solid/SolidboxRenderingStrategyDeserializer.h"
#include "Components/Graphics/Rendering/Scene/State/Deserialization/Primitives/CubeRenderingStrategyDeserializer.h"
#include "Components/Graphics/Rendering/Scene/State/Deserialization/Meshes/MeshRenderingStrategyDeserializer.h"
#include "Components/Graphics/Indexing/IndexingService.h"

#include "Components/Core/CoreService.h"

#ifdef _WIN32
#include "Components/Graphics/Win32GraphicService.h"
#include "Components/Events/Services/Win32EventService.h"
#elif __APPLE__
#include "Components/Graphics/CocoaGraphicsService.h"
#endif

#include "Components/Network/Http/NetworkService.h"
#include "Components/Network/WebSocket/WebSocketFactory.h"

using namespace TEngine;
using namespace TEngine::Components::Graphics;
using namespace TEngine::Components::Graphics::Rendering;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Textures;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;
using namespace TEngine::Components::Graphics::Rendering::Scene::Sequence;
using namespace TEngine::Components::Graphics::Rendering::Gui;
using namespace TEngine::Components::Graphics::CameraTracking;

using namespace TEngine::Components::Audio::Services::Readers;
using namespace TEngine::Components::Audio::Services;

using namespace TEngine::Components::Events::Services;

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Solid;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Empty;

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Empty;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Solid;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Meshes;

using namespace TEngine::Components::Graphics::Indexing;

using namespace TEngine::Components::Network::Http;

using namespace TEngine::Components::Core;


std::shared_ptr<IEngine> TEngine::createEngine(
#ifdef _WIN32
    HWND parent
#elif __APPLE__
    void *parent
#elif __ANDROID__
    android_app *parent
#endif
    ,
    bool isPhysicsEnabled)
{
        std::shared_ptr<IEventService> eventsService;

    if (parent)
    {
#ifdef _WIN32
        eventsService = std::make_shared<Win32EventService>();
#endif // _WIN32
    }
    else
    {
#ifdef TENGINE_USE_GLFW
        eventsService = std::make_shared<GlfwEventService>();
#else
        throw std::runtime_error("No event service available");
#endif
    }

    auto vorbisOggReader = std::make_shared<VorbisOggReader>();
    auto audioService = std::make_shared<AudioService>(vorbisOggReader);

    auto coreService = std::make_shared<CoreService>();

    auto imageLoadingService = std::make_shared<ImageLoadingService>();
    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto shadersService = std::make_shared<ShadersService>();
    auto bufferCacheService = std::make_shared<BuffersService>();
    auto texturesService = std::make_shared<TexturesService>(imageLoadingService);
    auto indexingService = std::make_shared<IndexingService>();
    auto meshService = std::make_shared<MeshService>(meshLoadingService, bufferCacheService, shadersService, texturesService, indexingService);
    auto physicsService = isPhysicsEnabled ? std::static_pointer_cast<IPhysicsService>(std::make_shared<PhysicsService>()) : std::static_pointer_cast<IPhysicsService>(std::make_shared<EmptyPhysicsService>());
    auto renderingSequenceService = std::make_shared<RenderingSequenceService>();

    auto buildinCameraTrackingStrategies = std::vector<std::shared_ptr<ICameraTrackingStrategy>>{
        std::make_shared<ListenerCameraTrackingStrategy>(audioService)};
    auto sceneService = std::make_shared<SceneService>(
        eventsService,
        shadersService,
        bufferCacheService,
        texturesService,
        meshService,
        physicsService,
        renderingSequenceService,
        buildinCameraTrackingStrategies);

    std::shared_ptr<IGuiService> guiService;
    std::shared_ptr<IGraphicsService> graphicsService;
    if (parent)
    {
#ifdef _WIN32
        guiService = std::make_shared<Win32GuiService>();
        graphicsService = std::make_shared<Win32GraphicService>(sceneService, guiService, meshLoadingService, texturesService, parent);
#elif __APPLE__
        graphicsService = std::make_shared<CocoaGraphicsService>(sceneService, guiService, meshLoadingService, texturesService, parent);
#endif
    }
    else
    {
#ifdef TENGINE_USE_GLFW
        guiService = std::make_shared<GlfwGuiService>(eventsService, texturesService);
        graphicsService = std::make_shared<GlfwGraphicsService>(sceneService, guiService, meshLoadingService, texturesService);
#else
        throw std::runtime_error("No graphics service available");
#endif
    }

    auto serializers = std::map<std::type_index, std::shared_ptr<Serializers::ISerializer>>();

    serializers[std::type_index(typeid(MeshRenderingStrategy))] =
        std::static_pointer_cast<Serializers::SerializerBase<MeshRenderingStrategy>>(std::make_shared<MeshRenderingStrategySerializer>());
    serializers[std::type_index(typeid(SolidboxRenderingStrategy))] =
        std::static_pointer_cast<Serializers::SerializerBase<SolidboxRenderingStrategy>>(std::make_shared<SolidboxRenderingStrategySerializer>());
    serializers[std::type_index(typeid(CubeRenderingStrategy))] =
        std::static_pointer_cast<Serializers::SerializerBase<CubeRenderingStrategy>>(std::make_shared<CubeRenderingStrategySerializer>());
    serializers[std::type_index(typeid(EmptyRenderingStrategy))] = std::make_shared<EmptyRenderingStrategySerializer>();

    auto serializationService = std::make_shared<SerializationService>(serializers);

    auto deserializers = std::map<std::string, std::shared_ptr<Deserializers::IDeserializer>>();
    deserializers["empty"] = std::make_shared<EmptyRenderingStrategyDeserializer>(sceneService);
    deserializers["solidbox"] = std::make_shared<SolidboxRenderingStrategyDeserializer>(sceneService);
    deserializers["cube"] = std::make_shared<CubeRenderingStrategyDeserializer>(sceneService);
    deserializers["mesh"] = std::make_shared<MeshRenderingStrategyDeserializer>(sceneService);

    auto deserializationService = std::make_shared<DeserializationService>(deserializers);

    auto networkService = std::make_shared<NetworkService>();
    auto webSocketFactory = std::make_shared<WebSocketFactory>();

    return std::make_shared<Engine>(
        graphicsService,
        eventsService,
        audioService,
        serializationService,
        deserializationService,
        networkService,
        webSocketFactory,
        coreService);
}