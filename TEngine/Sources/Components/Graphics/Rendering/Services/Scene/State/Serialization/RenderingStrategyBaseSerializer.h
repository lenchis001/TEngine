#ifndef TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H
#define TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H

#include "Components/State/Serialization/Serializers/SerializerBase.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/RenderingStrategyBase.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization
{
    class RenderingStrategyBaseSerializer : public virtual SerializerBase<RenderingStrategyBase>
    {
    protected:
        boost::json::value _serialize(std::shared_ptr<RenderingStrategyBase> value, serializeMember serializeMember) override;
    };
}

#endif // TENGINE_RENDERINGSTRATEGYBASESERIALIZER_H