#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include <memory>
#include <vector>

#include "IGraphicsService.h"

#include "Rendering/Services/IRenderingService.h"
#include "MeshLoading/Services/IMeshLoadingService.h"
#include "Rendering/Services/Textures/ITexturesService.h"
#include "Components/Audio/Services/IAudioService.h"
#include "Components/Graphics/Rendering/Services/CameraStrategies/Tracking/ICameraTrackingStrategy.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;
using namespace TEngine::Components::Graphics::Rendering::Services::Gui::ControlRenderingStrategies;
using namespace TEngine::Components::Audio::Services;

using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies::Tracking;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsService : public IGraphicsService
    {
    public:
        GraphicsService(
            std::shared_ptr<IRenderingService> renderingService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<ITexturesService> texturesService,
            std::shared_ptr<IAudioService> audioService);

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        bool isShutdownRequested() const override;

        double getTime() const override;

        inline void render() override
        {
            _renderingService->render();
        }

        std::shared_ptr<IRenderingStrategy> addPrimitive(
            PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        std::shared_ptr<IRenderingStrategy> addMesh(
            std::string path,
            std::shared_ptr<IRenderingStrategy> parent = nullptr) override;

        std::shared_ptr<ICameraStrategy> setActiveCamera(BuildinCameraTypes cameraType) override;

        void setActiveCamera(std::shared_ptr<ICameraStrategy> camera) override;

        std::shared_ptr<IWindowRenderingStrategy> addWindow() override;

    private:
        std::shared_ptr<IRenderingService> _renderingService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
        std::shared_ptr<ITexturesService> _texturesService;

        std::vector<std::shared_ptr<ICameraTrackingStrategy>> _cameraTrackingStrategies;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H