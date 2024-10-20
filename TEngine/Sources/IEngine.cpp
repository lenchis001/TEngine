#include "IEngine.h"

#include "memory"

#include "Engine.h"

#include "Components/Graphics/GlfwGraphicsService.h"
#include "Components/Graphics/Rendering/Services/Scene/SceneService.h"
#include "Components/Graphics/MeshLoading/Services/MeshLoadingService.h"
#include "Components/Graphics/Rendering/Services/Scene/Shaders/ShadersService.h"
#include "Components/Graphics/ImageLoading/Services/ImageLoadingService.h"
#include "Components/Graphics/Rendering/Services/Scene/Buffers/BuffersService.h"
#include "Components/Graphics/Rendering/Services/Textures/TexturesService.h"
#include "Components/Graphics/Rendering/Services/Scene/Meshes/MeshService.h"
#include "Components/Graphics/Rendering/Services/Scene/Lights/LightService.h"
#include "Components/Graphics/Rendering/Services/Scene/Physics/PhysicsService.h"
#include "Components/Graphics/Rendering/Services/Gui/GuiService.h"
#include "Components/Graphics/CameraTracking/ListenerCameraTrackingStrategy.h"
#include "Components/Audio/Services/Readers/VorbisOggReader.h"
#include "Components/Audio/Services/AudioService.h"
#include "Components/Events/Services/GlfwEventService.h"

#include "Components/State/Serialization/SerializationService.h"
#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/PhysicsRenderingDecoratorSerializer.h"
#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/RenderingOptimizationDecoratorSerializer.h"
#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/Meshes/MeshRenderingStrategySerializer.h"
#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/Solid/SolidboxRenderingStrategySerializer.h"
#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/Primitives/CubeRenderingStrategySerializer.h"
#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/RenderingStrategyBaseSerializer.h"
#include "Components/Graphics/State/Serialization/Vector3dSerializer.h"

#ifdef _WIN32
#include "Components/Graphics/Win32GraphicService.h"
#include "Components/Events/Services/Win32EventService.h"
#elif __APPLE__
#include "Components/Graphics/CocoaGraphicsService.h"
#endif

using namespace TEngine;
using namespace TEngine::Components::Graphics;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Services;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Lights;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Physics;
using namespace TEngine::Components::Graphics::Rendering::Services::Gui;
using namespace TEngine::Components::Graphics::CameraTracking;

using namespace TEngine::Components::Audio::Services::Readers;
using namespace TEngine::Components::Audio::Services;

using namespace TEngine::Components::Events::Services;

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Solid;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Solid;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Primitives;
using namespace TEngine::Components::Graphics::State::Serialization;

std::shared_ptr<IEngine> TEngine::createEngine(
#ifdef _WIN32
    HWND parent
#elif __APPLE__
    void *parent
#endif
)
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
        eventsService = std::make_shared<GlfwEventService>();
    }

    auto vorbisOggReader = std::make_shared<VorbisOggReader>();
    auto audioService = std::make_shared<AudioService>(vorbisOggReader);

    auto imageLoadingService = std::make_shared<ImageLoadingService>();
    auto meshLoadingService = std::make_shared<MeshLoadingService>();

    auto shadersService = std::make_shared<ShadersService>();
    auto bufferCacheService = std::make_shared<BuffersService>();
    auto texturesService = std::make_shared<TexturesService>(imageLoadingService);
    auto meshService = std::make_shared<MeshService>(meshLoadingService, bufferCacheService, shadersService, texturesService);
    auto lightServices = std::make_shared<LightService>();
    auto physicsService = std::make_shared<PhysicsService>();

    auto buildinCameraTrackingStrategies = std::vector<std::shared_ptr<ICameraTrackingStrategy>>{
        std::make_shared<ListenerCameraTrackingStrategy>(audioService)};
    auto sceneService = std::make_shared<SceneService>(eventsService, shadersService, bufferCacheService, texturesService, meshService, lightServices, physicsService, buildinCameraTrackingStrategies);

    auto guiService = std::make_shared<GuiService>(eventsService, texturesService);

    std::shared_ptr<IGraphicsService> graphicsService;
    if (parent)
    {
#ifdef _WIN32
        graphicsService = std::make_shared<Win32GraphicService>(sceneService, guiService, meshLoadingService, texturesService, parent);
#elif __APPLE__
        graphicsService = std::make_shared<CocoaGraphicsService>(sceneService, guiService, meshLoadingService, texturesService, parent);
#endif
    }
    else
    {
        graphicsService = std::make_shared<GlfwGraphicsService>(sceneService, guiService, meshLoadingService, texturesService);
    }

    auto serializers = std::map<std::type_index, std::shared_ptr<Serializers::ISerializer>>();

    serializers[std::type_index(typeid(PhysicsRenderingDecorator))] = std::make_shared<PhysicsRenderingDecoratorSerializer>();
    serializers[std::type_index(typeid(RenderingOptimizationDecorator))] = std::make_shared<RenderingOptimizationDecoratorSerializer>();
    serializers[std::type_index(typeid(MeshRenderingStrategy))] = 
        std::static_pointer_cast<Serializers::SerializerBase<MeshRenderingStrategy>>(std::make_shared<MeshRenderingStrategySerializer>());
    serializers[std::type_index(typeid(SolidboxRenderingStrategy))] = 
        std::static_pointer_cast<Serializers::SerializerBase<SolidboxRenderingStrategy>>(std::make_shared<SolidboxRenderingStrategySerializer>());
    serializers[std::type_index(typeid(CubeRenderingStrategy))] = 
        std::static_pointer_cast<Serializers::SerializerBase<CubeRenderingStrategy>>(std::make_shared<CubeRenderingStrategySerializer>());
    serializers[std::type_index(typeid(RenderingStrategyBase))] = std::make_shared<RenderingStrategyBaseSerializer>();
    serializers[std::type_index(typeid(Vector3df))] = std::make_shared<Vector3dSerializer<float>>();
    serializers[std::type_index(typeid(Vector3dd))] = std::make_shared<Vector3dSerializer<double>>();

    auto serializationService = std::make_shared<SerializationService>(serializers);

    return std::make_shared<Engine>(graphicsService, eventsService, audioService, serializationService);
}