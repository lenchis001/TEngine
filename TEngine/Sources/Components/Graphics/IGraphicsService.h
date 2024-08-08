#ifndef TENGINE_IGRAPHICSSERVICE_H
#define TENGINE_IGRAPHICSSERVICE_H

#include "future"

#include "Models/DataActionResult.h"

#include "Models/GraphicsParameters.h"
#include "Models/MeshLoading/ErrorCodes.h"
#include "Models/Rendering/RenderableObjects/IMeshRenderableObject.h"

using GraphicsParameters = TEngine::Components::Graphics::Models::GraphicsParameters;

using MeshLoadingErrorCodes = TEngine::Components::Graphics::Models::MeshLoading::MeshLoadingErrorCodes;
using IMeshRenderableObject = TEngine::Components::Graphics::Models::Rendering::RenderableObjects::IMeshRenderableObject;

using MeshLoadingDataActionResult = TEngine::Models::DataActionResult<MeshLoadingErrorCodes, IMeshRenderableObject>;

namespace TEngine::Components::Graphics::Services
{
    class IGraphicsService
    {
    public:
        virtual void initialize(GraphicsParameters& parameters) = 0;

        virtual void render() = 0;

        virtual std::future<MeshLoadingDataActionResult> loadMesh(const std::wstring &path) = 0;

        virtual ~IGraphicsService() = default;
    };
}

#endif // TENGINE_IGRAPHICSSERVICE_H