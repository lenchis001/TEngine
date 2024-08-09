#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include "IGraphicsService.h"

#include "Rendering/Services/IRenderingService.h"
#include "MeshLoading/Services/IMeshLoadingService.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Rendering::Services;
using namespace TEngine::Components::Graphics::MeshLoading::Services;
using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;
using namespace TEngine::Components::Graphics::MeshLoading::Models;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsService : public IGraphicsService
    {
    public:
        GraphicsService(std::shared_ptr<IRenderingService> renderingService, std::shared_ptr<IMeshLoadingService> meshLoadingService);

        void initialize(std::shared_ptr<IGraphicsParameters> parameters) override;

        void render() override;

        std::future<DataActionResult<ErrorCodes, IMeshRenderableObject>> loadMesh(const std::wstring &path) override;

        std::shared_ptr<IRenderableObject> addPrimitive(PrimitiveTypes type) override;

    private:
        std::shared_ptr<IRenderingService> _renderingService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H