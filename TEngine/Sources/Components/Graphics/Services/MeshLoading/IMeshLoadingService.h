#ifndef TENGINE_IMESHLOADINGSERVICE_H
#define TENGINE_IMESHLOADINGSERVICE_H

#include <future>

#include "Models/DataActionResult.h"

#include "Components/Graphics/Models/MeshLoading/ErrorCodes.h"
#include "Components/Graphics/Models/Rendering/RenderableObjects/IMeshRenderableObject.h"

using MeshLoadingErrorCodes = TEngine::Components::Graphics::Models::MeshLoading::MeshLoadingErrorCodes;
using IMeshRenderableObject = TEngine::Components::Graphics::Models::Rendering::RenderableObjects::IMeshRenderableObject;

using MeshLoadingDataActionResult = TEngine::Models::DataActionResult<MeshLoadingErrorCodes, IMeshRenderableObject>;

namespace TEngine::Components::Graphics::Services::MeshLoading
{
    class IMeshLoadingService
    {
    public:
        virtual std::future<MeshLoadingDataActionResult> loadMesh(const std::wstring& path) = 0;

        virtual ~IMeshLoadingService() = default;
    };
}

#endif //TENGINE_IMESHLOADINGSERVICE_H