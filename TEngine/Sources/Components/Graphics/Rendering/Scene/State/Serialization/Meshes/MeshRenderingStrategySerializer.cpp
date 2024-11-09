#include "MeshRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Serialization::Meshes;

MeshRenderingStrategySerializer::MeshRenderingStrategySerializer() : SerializerMixin("mesh")
{
}

boost::json::object MeshRenderingStrategySerializer::_serialize(
    MeshRenderingStrategy &value,
    serializeMember serializeMember)
{
    auto baseObject = SerializerMixin::_serializeBase(value, serializeMember);

    baseObject["path"] = value.getPath();

    return baseObject;
}