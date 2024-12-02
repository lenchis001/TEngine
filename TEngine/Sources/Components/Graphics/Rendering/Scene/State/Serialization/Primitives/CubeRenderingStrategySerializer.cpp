#include "CubeRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Primitives;

CubeRenderingStrategySerializer::CubeRenderingStrategySerializer() : SerializerMixin("cube")
{
}

boost::json::object CubeRenderingStrategySerializer::_serialize(
    CubeRenderingStrategy &value,
    serializeMember serializeMember)
{
    auto result = SerializerMixin::_serializeBase(value, serializeMember);

    result["texturePath"] = value.getTexture();

    return result;
}