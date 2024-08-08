#ifndef TENGINE_GRAPHICSSERVICE_H
#define TENGINE_GRAPHICSSERVICE_H

#include "IGraphicsService.h"

#include "memory"

#include "Services/Rendering/IRenderingService.h"
#include "Services/MeshLoading/IMeshLoadingService.h"

using namespace TEngine::Components::Graphics::Services::Rendering;
using namespace TEngine::Components::Graphics::Services::MeshLoading;

namespace TEngine::Components::Graphics::Services
{
    class GraphicsService : public IGraphicsService
    {
    public:
        GraphicsService(std::shared_ptr<IRenderingService> renderingService, std::shared_ptr<IMeshLoadingService> meshLoadingService);

        void initialize(GraphicsParameters& parameters) override;

        void render() override;

        std::future<MeshLoadingDataActionResult> loadMesh(const std::wstring &path) override;

    private:
        std::shared_ptr<IRenderingService> _renderingService;
        std::shared_ptr<IMeshLoadingService> _meshLoadingService;
    };
}

#endif // TENGINE_GRAPHICSSERVICE_H