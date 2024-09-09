#ifndef IMESH_SERVICE_H
#define IMESH_SERVICE_H

#include "string"
#include "memory"

#include "Components/Graphics/Rendering/Models/Meshes/IRenderableMesh.h"

namespace TEngine::Components::Graphics::Rendering::Services::Meshes
{
    class IMeshService
    {
    public:
        virtual ~IMeshService() = default;

        virtual std::shared_ptr<Models::Meshes::IRenderableMesh> take(const std::string &path) = 0;

        virtual void release(std::shared_ptr<Models::Meshes::IRenderableMesh> renderableMesh) = 0;
    };
}

#endif // IMESH_SERVICE_H