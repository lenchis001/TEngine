#include "SolidboxRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Solid;

SolidboxRenderingStrategySerializer::SolidboxRenderingStrategySerializer()
{
    setType("solidbox");
}

boost::json::value SolidboxRenderingStrategySerializer::_serialize(
    SolidboxRenderingStrategy& value,
    serializeMember serializeMember)
{
    auto result = RenderingStrategyBaseSerializer::_serialize(value, serializeMember);

    return result;
}