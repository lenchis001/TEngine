#include "EmptyRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Empty;

EmptyRenderingStrategySerializer::EmptyRenderingStrategySerializer(): SerializerMixin("empty")
{
}

boost::json::object EmptyRenderingStrategySerializer::_serialize(
    EmptyRenderingStrategy& value,
    serializeMember serializeMember)
{
    auto result = SerializerMixin::_serializeBase(value, serializeMember);

    return result;
}