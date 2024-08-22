#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include "IGraphicsService.h"

#include "Rendering/Services/IRenderingService.h"
#include "MeshLoading/Services/IMeshLoadingService.h"
#include "ImageLoading/Services/IImageLoadingService.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Cameras;
using namespace TEngine::Components::Graphics::Rendering::Services::CameraStrategies;
using namespace TEngine::Components::Graphics::ImageLoading::Services;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsService : public IGraphicsService
    {
    public:
        GraphicsService(
            std::shared_ptr<IRenderingService> renderingService,
            std::shared_ptr<IMeshLoadingService> meshLoadingService,
            std::shared_ptr<IImageLoadingService> imageLoadingService);

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        double getTime() const override;

        void render() override;

        std::future<DataActionResult<ErrorCodes, IMeshRenderableObject>> loadMesh(const std::wstring &path) override;

        std::shared_ptr<IRenderableObject> addPrimitive(
            PrimitiveTypes type,
            std::string texturePath,
            std::shared_ptr<IRenderableObject> parent = nullptr) override;

        std::shared_ptr<ICameraStrategy> setActiveCamera(BuildinCameraTypes cameraType) override;

        void setActiveCamera(std::shared_ptr<ICameraStrategy> camera) override;

    private:
        std::shared_ptr<IRenderingService> _renderingService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
        std::shared_ptr<IImageLoadingService> _imageLoadingService;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H