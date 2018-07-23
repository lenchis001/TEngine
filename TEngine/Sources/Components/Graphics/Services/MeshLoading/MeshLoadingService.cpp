#include "MeshLoadingService.h"

namespace TEngine::Components::Graphics::Services::MeshLoading
{
    std::future<MeshLoadingDataActionResult> MeshLoadingService::loadMesh(const std::wstring& path)
    {
        return std::async(std::launch::async, [path]() -> MeshLoadingDataActionResult
        {
                throw "";
        });
    }
}