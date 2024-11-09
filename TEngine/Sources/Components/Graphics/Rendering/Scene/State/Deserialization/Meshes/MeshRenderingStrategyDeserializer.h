#ifndef TENGINE_MESHRENDERINGSTRATEGYDESERIALIZER_H
#define TENGINE_MESHRENDERINGSTRATEGYDESERIALIZER_H

#include "Components/Graphics/Rendering/Scene/State/Deserialization/DeserializerMixin.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization;
using namespace TEngine::Components::State::Deserialization::Deserializers;

namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Meshes
{
    class MeshRenderingStrategyDeserializer : public DeserializerMixin, public DeserializerBase<IRenderingStrategy>
    {
    public:
        MeshRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService);

    protected:
        void _deserialize(const boost::json::value &value, deserializeMember deserializeMember, std::shared_ptr<IRenderingStrategy> root) override;
    };
}

#endif // TENGINE_MESHRENDERINGSTRATEGYDESERIALIZER_H