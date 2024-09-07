#ifndef TENGINE_MESHRENDERINGSTRATEGY_H
#define TENGINE_MESHRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Services/RenderingStrategies/RenderingStrategyBase.h"

#include "Components/Graphics/Rendering/Services/Meshes/IMeshService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Meshes;

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes
{
    class MeshRenderingStrategy : public RenderingStrategyBase
    {
    public:
        MeshRenderingStrategy(
            std::shared_ptr<IMeshService> meshService
    );

        void render(
            const Matrix4x4f &vpMatrix,
            const Components::Graphics::Models::Vector3df &cameraPosition);

    private:
        void _prepareMesh();

        std::shared_ptr<IMeshService> _meshService;
    };
}

#endif // TENGINE_MESHRENDERINGSTRATEGY_H