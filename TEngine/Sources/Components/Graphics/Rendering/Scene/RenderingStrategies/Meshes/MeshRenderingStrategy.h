#ifndef TENGINE_MESHRENDERINGSTRATEGY_H
#define TENGINE_MESHRENDERINGSTRATEGY_H

#include "IMeshRenderingStrategy.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Physics/PhysicsRenderingStrategyBase.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Light/LightRenderingStrategyBase.h"

#include "Components/Graphics/Rendering/Models/Meshes/IRenderableMesh.h"
#include "Components/Graphics/Rendering/Scene/Meshes/IMeshService.h"
#include "Components/Graphics/Rendering/Scene/Physics/IPhysicsService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Models::Priority;
using namespace TEngine::Components::Graphics::Rendering::Scene::Meshes;
using namespace TEngine::Components::Graphics::Rendering::Scene::Lights;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingMixins;
using namespace TEngine::Components::Graphics::Rendering::Textures;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Meshes
{
    class MeshRenderingStrategy : 
        public RenderingStrategies::Physics::PhysicsRenderingStrategyBase, 
        public RenderingStrategies::Light::LightRenderingStrategyBase,
        public IMeshRenderingStrategy
    {
    public:
        MeshRenderingStrategy(
            std::shared_ptr<IMeshService> meshService,
            std::shared_ptr<ILightService> lightServices,
            std::shared_ptr<IPhysicsService> physicsService,
            std::shared_ptr<ITexturesService> textureService,
            OnDeleteCallback onDeleteCallback,
            const std::string &path);
        ~MeshRenderingStrategy();

        std::type_index getType() const override;

        void setPosition(const Vector3df &position) override;

        void setRotation(const Vector3df &rotation) override;

        const std::string &getPath() const;

        RenderingPriority getRenderingPriority() const override;

        const Graphics::Models::Vector3df& getSize() const override;

    protected:
        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        std::vector<float> _getVertices() const override;

        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;

        void _onDetachedFromParent() override;

    private:
        std::shared_ptr<IRenderableMesh> _renderableMesh;
        std::shared_ptr<IMeshService> _meshService;
        std::shared_ptr<ITexturesService> _textureService;

        const std::string _path;
        Vector3df _size;
    };
}

#endif // TENGINE_MESHRENDERINGSTRATEGY_H