#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include "IGraphicsService.h"

#include "memory"

#include "Services/Rendering/IRenderingService.h"
#include "Services/MeshLoading/IMeshLoadingService.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Services::Rendering;
using namespace TEngine::Components::Graphics::Services::MeshLoading;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Models::Rendering::RenderableObjects;
using namespace TEngine::Components::Graphics::Models::MeshLoading;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsService : public IGraphicsService
    {
    public:
        GraphicsService(std::shared_ptr<IRenderingService> renderingService, std::shared_ptr<IMeshLoadingService> meshLoadingService);

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void render() override;

        std::future<DataActionResult<MeshLoadingErrorCodes, IMeshRenderableObject>> loadMesh(const std::wstring &path) override;

    private:
        std::shared_ptr<IRenderingService> _renderingService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H