#ifndef TENGINE_IMESHLOADINGSERVICE_H
#define TENGINE_IMESHLOADINGSERVICE_H

#include <future>

#include "Models/DataActionResult.h"

#include "Components/Graphics/MeshLoading/Models/ErrorCodes.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IMeshRenderableObject.h"
#include "Components/Graphics/Models/PrimitiveTypes.h"

namespace TEngine::Components::Graphics::MeshLoading::Services
{
    class IMeshLoadingService
    {
    public:
        virtual std::future<
            TEngine::Models::DataActionResult<
            TEngine::Components::Graphics::MeshLoading::Models::ErrorCodes,
            TEngine::Components::Graphics::Rendering::Models::RenderableObjects::IMeshRenderableObject
            >
        > loadMesh(const std::wstring& path) = 0;

        virtual ~IMeshLoadingService() = default;
    };
}

#endif //TENGINE_IMESHLOADINGSERVICE_H