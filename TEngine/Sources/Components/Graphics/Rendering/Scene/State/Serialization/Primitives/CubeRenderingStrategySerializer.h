#include "Components/Graphics/Rendering/Scene/State/Serialization/SerializerMixin.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Primitives/CubeRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;

namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Primitives
{
    class CubeRenderingStrategySerializer : public SerializerMixin, public SerializerBase<CubeRenderingStrategy>
    {
    public:
        CubeRenderingStrategySerializer();
    protected:
        boost::json::object _serialize(
            CubeRenderingStrategy& value,
            serializeMember serializeMember) override;
    };
}