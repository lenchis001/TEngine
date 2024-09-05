#ifndef TENGINE_IMESHLOADINGSERVICE_H
#define TENGINE_IMESHLOADINGSERVICE_H

#include "Components/Graphics/MeshLoading/Models/IMesh.h"

namespace TEngine::Components::Graphics::MeshLoading::Services
{
    class IMeshLoadingService
    {
    public:
        virtual void initialize() = 0;
        
        virtual std::shared_ptr<Components::Graphics::MeshLoading::Models::IMesh> load(const std::string &path) = 0;

        virtual ~IMeshLoadingService() = default;
    };
}

#endif // TENGINE_IMESHLOADINGSERVICE_H