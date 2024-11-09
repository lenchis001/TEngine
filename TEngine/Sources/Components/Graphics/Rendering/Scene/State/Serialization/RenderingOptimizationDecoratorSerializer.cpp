#include "RenderingOptimizationDecoratorSerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization;

boost::json::object RenderingOptimizationDecoratorSerializer::_serialize(
    RenderingOptimizationDecorator& value,
    serializeMember serializeMember)
{
    auto internalStrategy = value.getInternalStrategy();
    auto internalSerialized = serializeMember(*internalStrategy);

    return internalSerialized;
}