#include "MeshLoadingService.h"

namespace TEngine::Components::Graphics::Services::MeshLoading
{
    std::future<DataActionResult<MeshLoadingErrorCodes, IMeshRenderableObject>> MeshLoadingService::loadMesh(const std::wstring& path)
    {
        return std::async(std::launch::async, [path]() -> DataActionResult<MeshLoadingErrorCodes, IMeshRenderableObject>
        {
                throw "";
        });
    }
}