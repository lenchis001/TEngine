#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/SerializerMixin.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/Meshes/MeshRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Meshes;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Meshes
{
    class MeshRenderingStrategySerializer : public SerializerMixin, public SerializerBase<MeshRenderingStrategy>
    {
        public:
            MeshRenderingStrategySerializer();
        protected:
            boost::json::object _serialize(
                MeshRenderingStrategy& value,
                serializeMember serializeMember) override;
    };
}