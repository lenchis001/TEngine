#ifndef TENGINE_IGRAPHICSSERVICE_H
#define TENGINE_IGRAPHICSSERVICE_H

#include "future"

#include "Models/DataActionResult.h"

#include "Models/IGraphicsParameters.h"
#include "Models/MeshLoading/ErrorCodes.h"
#include "Models/Rendering/RenderableObjects/IMeshRenderableObject.h"

namespace TEngine::Components::Graphics::Services
{
    class IGraphicsService
    {
    public:
        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Models::IGraphicsParameters> parameters) = 0;

        virtual void render() = 0;

        virtual std::future<
            TEngine::Models::DataActionResult<
                TEngine::Components::Graphics::Models::MeshLoading::MeshLoadingErrorCodes,
                TEngine::Components::Graphics::Models::Rendering::RenderableObjects::IMeshRenderableObject
            >
        > loadMesh(const std::wstring &path) = 0;

        virtual ~IGraphicsService() = default;
    };
}

#endif // TENGINE_IGRAPHICSSERVICE_H