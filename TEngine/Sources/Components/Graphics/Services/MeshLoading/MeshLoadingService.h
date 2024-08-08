#ifndef TENGINE_MESHLOADINGSERVICE_H
#define TENGINE_MESHLOADINGSERVICE_H

#include "IMeshLoadingService.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Models::MeshLoading;
using namespace TEngine::Components::Graphics::Models::Rendering::RenderableObjects;


namespace TEngine::Components::Graphics::Services::MeshLoading
{
    class MeshLoadingService : public IMeshLoadingService
    {
    public:
        std::future<DataActionResult<MeshLoadingErrorCodes, IMeshRenderableObject>> loadMesh(const std::wstring& path) override;
    private:
        
    };
}

#endif //TENGINE_MESHLOADINGSERVICE_H