#include "MeshRenderingStrategySerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization::Meshes;

boost::json::value MeshRenderingStrategySerializer::_serialize(
    std::shared_ptr<MeshRenderingStrategy> value,
    serializeMember serializeMember)
{
    auto baseObject = RenderingStrategyBaseSerializer::_serialize(value, serializeMember);

    return baseObject;
}