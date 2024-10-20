#include "CubeRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Primitives;

CubeRenderingStrategySerializer::CubeRenderingStrategySerializer()
{
    setType("cube");
}

boost::json::value CubeRenderingStrategySerializer::_serialize(
    CubeRenderingStrategy& value,
    serializeMember serializeMember)
{
    auto result = RenderingStrategyBaseSerializer::_serialize(value, serializeMember);

    return result;
}