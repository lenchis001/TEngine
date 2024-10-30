#include "SolidboxRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Solid;

SolidboxRenderingStrategySerializer::SolidboxRenderingStrategySerializer(): SerializerMixin("solidbox")
{
}

boost::json::object SolidboxRenderingStrategySerializer::_serialize(
    SolidboxRenderingStrategy& value,
    serializeMember serializeMember)
{
    auto result = SerializerMixin::_serializeBase(value, serializeMember);

    return result;
}