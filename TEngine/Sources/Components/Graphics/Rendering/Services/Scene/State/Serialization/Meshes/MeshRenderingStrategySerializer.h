#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/RenderingStrategyBaseSerializer.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/Meshes/MeshRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Meshes;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Meshes
{
    class MeshRenderingStrategySerializer : public RenderingStrategyBaseSerializer, public virtual SerializerBase<MeshRenderingStrategy>
    {
        protected:
            boost::json::value _serialize(
                std::shared_ptr<MeshRenderingStrategy> value,
                serializeMember serializeMember) override;
    };
}