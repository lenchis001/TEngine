#ifndef TENGINE_MESHRENDERINGSTRATEGY_H
#define TENGINE_MESHRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include "Components/Graphics/Rendering/Models/Meshes/IRenderableMesh.h"
#include "Components/Graphics/Rendering/Scene/Meshes/IMeshService.h"
#include "Components/Graphics/Rendering/Scene/Lights/ILightServices.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes
{
    class MeshRenderingStrategy : public RenderingStrategyBase
    {
    public:
        MeshRenderingStrategy(
            std::shared_ptr<IMeshService> meshService,
            std::shared_ptr<ILightServices> lightServices,
            const std::string &path);
        ~MeshRenderingStrategy();

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        std::vector<float> getVertices() const override;

        std::type_index getType() const override;

        const std::string &getPath() const;

    private:
        std::shared_ptr<IRenderableMesh> _renderableMesh;
        std::shared_ptr<IMeshService> _meshService;
        std::shared_ptr<ILightServices> _lightServices;

        const std::string _path;
    };
}

#endif // TENGINE_MESHRENDERINGSTRATEGY_H