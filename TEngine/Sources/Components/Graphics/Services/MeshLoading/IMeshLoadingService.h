#ifndef TENGINE_IMESHLOADINGSERVICE_H
#define TENGINE_IMESHLOADINGSERVICE_H

#include <future>

#include "Models/DataActionResult.h"

#include "Components/Graphics/Models/MeshLoading/ErrorCodes.h"
#include "Components/Graphics/Models/Rendering/RenderableObjects/IMeshRenderableObject.h"

namespace TEngine::Components::Graphics::Services::MeshLoading
{
    class IMeshLoadingService
    {
    public:
        virtual std::future<
            TEngine::Models::DataActionResult<
            TEngine::Components::Graphics::Models::MeshLoading::MeshLoadingErrorCodes,
            TEngine::Components::Graphics::Models::Rendering::RenderableObjects::IMeshRenderableObject
            >
        > loadMesh(const std::wstring& path) = 0;

        virtual ~IMeshLoadingService() = default;
    };
}

#endif //TENGINE_IMESHLOADINGSERVICE_H