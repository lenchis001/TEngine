#ifndef TENGINE_EMPTYRENDERINGSTRATEGYSERIALIZER_H
#define TENGINE_EMPTYRENDERINGSTRATEGYSERIALIZER_H

#include "Components/Graphics/Rendering/Services/Scene/State/Serialization/SerializerMixin.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/Empty/EmptyRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Empty;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Empty
{
    class EmptyRenderingStrategySerializer : public SerializerMixin, public SerializerBase<EmptyRenderingStrategy>
    {
    public:
        EmptyRenderingStrategySerializer();

    protected:
        boost::json::object _serialize(
            EmptyRenderingStrategy &value,
            serializeMember serializeMember) override;
    };
}

#endif // TENGINE_EMPTYRENDERINGSTRATEGYSERIALIZER_H