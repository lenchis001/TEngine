#include "MeshRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Meshes;

MeshRenderingStrategySerializer::MeshRenderingStrategySerializer()
{
    setType("mesh");
}

boost::json::object MeshRenderingStrategySerializer::_serialize(
    MeshRenderingStrategy& value,
    serializeMember serializeMember)
{
    auto baseObject = RenderingStrategyBaseSerializer::_serialize(value, serializeMember);

    baseObject["path"] = value.getPath();

    return baseObject;
}