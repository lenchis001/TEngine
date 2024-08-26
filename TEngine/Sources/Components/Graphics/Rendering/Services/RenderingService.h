#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

#include "vector"

#include "GLFW/glfw3.h"

#include "RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Services/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Services/Textures/ITexturesService.h"
#include "Components/Graphics/Rendering/Services/Optimization/IBigWorldService.h"

using namespace TEngine::Components::Graphics::Rendering::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Graphics::Rendering::Services::Optimization;

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services
{
    class RenderingService : public IRenderingService
    {
    public:
        RenderingService(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::shared_ptr<IBigWorldService> bigWorldService);
        ~RenderingService();

        void initialize(std::shared_ptr<IRenderingParameters> parameters) override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        std::shared_ptr<IRenderableObject> addToRendering(
            PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<IRenderableObject> parent = nullptr) override;

        void render() override;

        std::shared_ptr<ICameraStrategy> setActiveCamera(BuildinCameraTypes cameraType) override;

        void setActiveCamera(std::shared_ptr<ICameraStrategy> camera) override;

    private:
        void _onWindowResized(int width, int height);

        bool _isBigWorldOptimizationEnabled;

        GLFWwindow *_window;

        std::shared_ptr<IRenderableObject> _root;
        std::shared_ptr<ICameraStrategy> _activeCamera;
        std::vector<std::shared_ptr<IRenderingStrategy>> _strategies;
        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _textureService;
        std::shared_ptr<IBigWorldService> _bigWorldService;
    };
}

#endif // TENGINE_RENDERINGSERVICE_H