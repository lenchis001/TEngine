#include "CubeRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Primitives;

CubeRenderingStrategySerializer::CubeRenderingStrategySerializer()
{
    setType("cube");
}

boost::json::object CubeRenderingStrategySerializer::_serialize(
    CubeRenderingStrategy& value,
    serializeMember serializeMember)
{
    auto result = RenderingStrategyBaseSerializer::_serialize(value, serializeMember);

    result["texturePath"] = value.getTexturePath();

    return result;
}