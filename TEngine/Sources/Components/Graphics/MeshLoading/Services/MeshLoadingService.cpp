#include "MeshLoadingService.h"

using namespace TEngine::Components::Graphics::MeshLoading::Services;

    MeshLoadingService::MeshLoadingService()
    {
    }


    std::future<DataActionResult<ErrorCodes, IRenderingStrategy>> MeshLoadingService::loadMesh(const std::wstring& path)
    {
        return std::async(std::launch::async, [path]() -> DataActionResult<ErrorCodes, IRenderingStrategy>
        {
                throw "";
        });
    }
