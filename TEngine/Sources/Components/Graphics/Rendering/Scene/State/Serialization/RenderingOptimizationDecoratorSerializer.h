#include "Components/State/Serialization/Serializers/SerializerBase.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingOptimizationDecorator.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization
{
    class RenderingOptimizationDecoratorSerializer : public SerializerBase<RenderingOptimizationDecorator>
    {
        protected:
            boost::json::object _serialize(RenderingOptimizationDecorator& value, serializeMember serializeMember) override;
    };
}