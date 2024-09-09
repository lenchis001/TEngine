#ifndef TENGINE_MESHRENDERINGSTRATEGY_H
#define TENGINE_MESHRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Services/RenderingStrategies/RenderingStrategyBase.h"

#include "Components/Graphics/Rendering/Models/Meshes/IRenderableMesh.h"
#include "Components/Graphics/Rendering/Services/Meshes/IMeshService.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Services::Meshes;

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Meshes
{
    class MeshRenderingStrategy : public RenderingStrategyBase
    {
    public:
        MeshRenderingStrategy(
            std::shared_ptr<IMeshService> meshService,
            const std::string &path);
        ~MeshRenderingStrategy();

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy);

    private:
        std::shared_ptr<Models::Meshes::IRenderableMesh> _renderableMesh;
        std::shared_ptr<IMeshService> _meshService;
    };
}

#endif // TENGINE_MESHRENDERINGSTRATEGY_H