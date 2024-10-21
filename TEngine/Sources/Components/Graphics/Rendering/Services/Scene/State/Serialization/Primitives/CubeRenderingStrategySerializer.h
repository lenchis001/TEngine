#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/RenderingStrategyBaseSerializer.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/Primitives/CubeRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Primitives;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Primitives
{
    class CubeRenderingStrategySerializer : public RenderingStrategyBaseSerializer, public virtual SerializerBase<CubeRenderingStrategy>
    {
    public:
        CubeRenderingStrategySerializer();
    protected:
        boost::json::object _serialize(
            CubeRenderingStrategy& value,
            serializeMember serializeMember) override;
    };
}