#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

#include "vector"

#include "GLFW/glfw3.h"

#include "Mixins/ContextAwareMixin.h"

#include "Components/Events/Services/IEventService.h"

#include "RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Services/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Services/Textures/ITexturesService.h"
#include "Components/Graphics/Rendering/Services/Meshes/IMeshService.h"
#include "Components/Graphics/Rendering/Services/Lights/ILightServices.h"

using namespace TEngine::Components::Events::Services;

using namespace TEngine::Components::Graphics::Rendering::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Services::Lights;

using namespace TEngine::Mixins;

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services
{
    class RenderingService : public IRenderingService, public ContextAwareMixin<RenderingService>
    {
    public:
        RenderingService(
            std::shared_ptr<IEventService> eventService,
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::shared_ptr<IMeshService> meshService,
            std::shared_ptr<ILightServices> lightServices);
        ~RenderingService();

        void initialize(std::shared_ptr<IRenderingParameters> parameters) override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        std::shared_ptr<IRenderingStrategy> addToRendering(
            PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        std::shared_ptr<IRenderingStrategy> addMeshToRendering(
            std::string meshPath,
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        void render() override;

        std::shared_ptr<ICameraStrategy> setActiveCamera(BuildinCameraTypes cameraType) override;

        void setActiveCamera(std::shared_ptr<ICameraStrategy> camera) override;

    private:
        static void _onWindowResized(GLFWwindow* window, int width, int height);

        GLFWwindow *_window;

        std::shared_ptr<IEventService> _eventService;

        std::shared_ptr<IRenderingStrategy> _root;
        std::shared_ptr<ICameraStrategy> _activeCamera;
        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _textureService;
        std::shared_ptr<IMeshService> _meshService;
        std::shared_ptr<ILightServices> _lightServices;
    };
}

#endif // TENGINE_RENDERINGSERVICE_H