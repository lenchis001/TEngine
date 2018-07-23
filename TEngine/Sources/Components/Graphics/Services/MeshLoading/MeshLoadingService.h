#ifndef TENGINE_MESHLOADINGSERVICE_H
#define TENGINE_MESHLOADINGSERVICE_H

#include "IMeshLoadingService.h"

namespace TEngine::Components::Graphics::Services::MeshLoading
{
    class MeshLoadingService : public IMeshLoadingService
    {
    public:
        std::future<MeshLoadingDataActionResult> loadMesh(const std::wstring& path) override;
    private:
        
    };
}

#endif //TENGINE_MESHLOADINGSERVICE_H