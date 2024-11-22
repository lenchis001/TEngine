#include "MeshRenderingStrategyDeserializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Meshes;

MeshRenderingStrategyDeserializer::MeshRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService) : DeserializerMixin(sceneService)
{
}

void MeshRenderingStrategyDeserializer::_deserialize(
    const boost::json::value &value,
    deserializeMember deserializeMember,
    std::shared_ptr<IRenderingStrategy> root)
{
    auto serializedObject = value.as_object();

    auto position = _deserializePosition(serializedObject);
    auto rotation = _deserializeRotation(serializedObject);
    auto scale = _deserializeScale(serializedObject);

    auto path = std::string(serializedObject.at("path").as_string().c_str());

    auto physicsFlagString = serializedObject.contains("physicsFlags") ? std::string(serializedObject.at("physicsFlags").as_string().c_str()) : "none";
    auto physicsFlag = _toPhysicsFlag(physicsFlagString);

    auto mesh = _sceneService->addMesh(
        path,
        root,
        physicsFlag);

    mesh->setPosition(position);
    mesh->setRotation(rotation);
    mesh->setScale(scale);

    DeserializerMixin::_deserializeBase(value, deserializeMember, mesh);
}