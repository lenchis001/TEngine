#ifndef TENGINE_MESHLOADINGSERVICE_H
#define TENGINE_MESHLOADINGSERVICE_H

#include "IMeshLoadingService.h"

#include "map"

#include "Components/Graphics/Models/PrimitiveTypes.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::MeshLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects;

namespace TEngine::Components::Graphics::MeshLoading::Services
{
    class MeshLoadingService : public IMeshLoadingService
    {
    public:
        MeshLoadingService();

        std::future<DataActionResult<ErrorCodes, IMeshRenderableObject>> loadMesh(const std::wstring& path) override;
    private:
    };
}

#endif //TENGINE_MESHLOADINGSERVICE_H