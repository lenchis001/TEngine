#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/RenderingStrategyBaseSerializer.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/Solid/SolidboxRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Solid;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Solid
{
    class SolidboxRenderingStrategySerializer : public RenderingStrategyBaseSerializer, public virtual SerializerBase<SolidboxRenderingStrategy>
    {
    public:
        SolidboxRenderingStrategySerializer();
    protected:
        boost::json::object _serialize(
            SolidboxRenderingStrategy& value,
            serializeMember serializeMember) override;
    };
}