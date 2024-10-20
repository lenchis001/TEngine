#include "Components/State/Serialization/Serializers/SerializerBase.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/RenderingOptimizationDecorator.h"

using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Serialization::Serializers;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization
{
    class RenderingOptimizationDecoratorSerializer : public SerializerBase<RenderingOptimizationDecorator>
    {
        protected:
            boost::json::value _serialize(RenderingOptimizationDecorator& value, serializeMember serializeMember) override;
    };
}