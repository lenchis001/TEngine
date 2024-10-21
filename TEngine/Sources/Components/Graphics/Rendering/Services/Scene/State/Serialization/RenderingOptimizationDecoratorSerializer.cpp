#include "RenderingOptimizationDecoratorSerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization;

boost::json::object RenderingOptimizationDecoratorSerializer::_serialize(
    RenderingOptimizationDecorator& value,
    serializeMember serializeMember)
{
    auto internalStrategy = value.getInternalStrategy();
    auto internalSerialized = serializeMember(*internalStrategy);

    return internalSerialized;
}