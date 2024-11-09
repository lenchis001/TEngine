#include "CubeRenderingStrategyDeserializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Primitives;
using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

CubeRenderingStrategyDeserializer::CubeRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService) : DeserializerMixin(sceneService)
{
}

void CubeRenderingStrategyDeserializer::_deserialize(
    const boost::json::value &value,
    deserializeMember deserializeMember,
    std::shared_ptr<IRenderingStrategy> root)
{
    auto serializedObject = value.as_object();

    auto position = _deserializePosition(serializedObject);
    auto rotation = _deserializeRotation(serializedObject);
    auto scale = _deserializeScale(serializedObject);

    auto texturePath = std::string(serializedObject.at("texturePath").as_string().c_str());

    auto physicsFlagString = serializedObject.contains("physicsFlags") ? std::string(serializedObject.at("physicsFlags").as_string().c_str()) : "none";
    auto physicsFlag = _toPhysicsFlag(physicsFlagString);

    auto cube = _sceneService->addPrimitive(
        PrimitiveTypes::Cube,
        texturePath,
        root,
        physicsFlag);

    cube->setPosition(position);
    cube->setRotation(rotation);
    cube->setScale(scale);

    DeserializerMixin::_deserializeBase(value, deserializeMember, cube);
}