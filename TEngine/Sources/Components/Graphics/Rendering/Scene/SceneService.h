#ifndef TENGINE_SCENESERVICE_H
#define TENGINE_SCENESERVICE_H

#include "ISceneService.h"

#include <vector>

#include "Components/Events/Services/IEventService.h"

#include "RenderingStrategies/IRenderingStrategy.h"
#include "Shaders/IShadersService.h"
#include "Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"
#include "Meshes/IMeshService.h"
#include "Lights/ILightServices.h"
#include "Physics/IPhysicsService.h"
#include "CameraStrategies/Tracking/ICameraTrackingStrategy.h"

#include "Components/Graphics/Models/Vector2d.h"

using namespace TEngine::Components::Events::Services;

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Physics;
using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;
using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies::Tracking;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;

namespace TEngine::Components::Graphics::Rendering::Scene
{
    class SceneService : public ISceneService
    {
    public:
        SceneService(
            std::shared_ptr<IEventService> eventService,
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::shared_ptr<IMeshService> meshService,
            std::shared_ptr<ILightServices> lightServices,
            std::shared_ptr<IPhysicsService> physicsService,
            std::vector<std::shared_ptr<ICameraTrackingStrategy>> buildinCameraTrackingStrategies);

        void initialize() override;

        void deinitialize() override;

        std::shared_ptr<ICubeRenderingStrategy> addCube(
            std::string texturePath = "",
            std::shared_ptr<IRenderingStrategy> parent = nullptr,
            PhysicsFlags physicsFlags = PhysicsFlags::NONE) override;

        std::shared_ptr<IMeshRenderingStrategy> addMesh(
            std::string path,
            std::shared_ptr<IRenderingStrategy> parent = nullptr,
            PhysicsFlags physicsFlags = PhysicsFlags::NONE) override;

        std::shared_ptr<ISolidboxRenderingStrategy> addSolidbox(
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        std::shared_ptr<IRenderingStrategy> addEmpty(
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        std::shared_ptr<IRenderingStrategy> addSkySphere(
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        void render(double time) override;

        std::shared_ptr<ICameraStrategy> getActiveCamera() override;

        std::shared_ptr<ICameraStrategy> setActiveCamera(BuildinCameraTypes cameraType) override;

        void setActiveCamera(std::shared_ptr<ICameraStrategy> camera) override;

        std::shared_ptr<IRenderingStrategy> getRoot() override;

    private:

        Vector2di _getWindowSize() const;

        std::shared_ptr<IEventService> _eventService;

        std::shared_ptr<IRenderingStrategy> _root;
        std::shared_ptr<ICameraStrategy> _activeCamera;
        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _textureService;
        std::shared_ptr<IMeshService> _meshService;
        std::shared_ptr<ILightServices> _lightServices;
        std::shared_ptr<IPhysicsService> _physicsService;

        std::vector<std::shared_ptr<ICameraTrackingStrategy>> _buildinCameraTrackingStrategies;
    };
}

#endif // TENGINE_SCENESERVICE_H