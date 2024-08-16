#ifndef TENGINE_RENDERINGSERVICE_H
#define TENGINE_RENDERINGSERVICE_H

#include "IRenderingService.h"

#include "vector"

#include "GLFW/glfw3.h"

#include "RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Services/Shaders/IShadersService.h"

using namespace TEngine::Components::Graphics::Rendering::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services
{
    class RenderingService : public IRenderingService
    {
    public:
        RenderingService(std::shared_ptr<IShadersService> shadersService);

        void initialize(std::shared_ptr<IRenderingParameters> parameters) override;

        std::shared_ptr<IRenderableObject> addToRendering(PrimitiveTypes type, std::shared_ptr<IRenderableObject> parent = nullptr) override;

        void render() override;

        std::shared_ptr<ICameraStrategy> setActiveCamera(BuildinCameraTypes cameraType) override;

        void setActiveCamera(std::shared_ptr<ICameraStrategy> camera) override;

    private:
        GLFWwindow *_window;

        std::shared_ptr<IRenderableObject> _root;
        std::shared_ptr<ICameraStrategy> _activeCamera;
        std::vector<std::shared_ptr<IRenderingStrategy>> _strategies;
        std::shared_ptr<IShadersService> _shadersService;

        double _lastTime;
        int _nbFrames;
    };
}

#endif // TENGINE_RENDERINGSERVICE_H