#ifndef TENGINE_SOLIDRENDERINGSTRATEGY_H
#define TENGINE_SOLIDRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/State/Serialization/SerializerMixin.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Solid/SolidboxRenderingStrategy.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;

namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Solid
{
    class SolidboxRenderingStrategySerializer : public SerializerMixin, public SerializerBase<SolidboxRenderingStrategy>
    {
    public:
        SolidboxRenderingStrategySerializer();
    protected:
        boost::json::object _serialize(
            SolidboxRenderingStrategy& value,
            serializeMember serializeMember) override;
    };
}

#endif // TENGINE_SOLIDRENDERINGSTRATEGY_H