#include "EmptyRenderingStrategyDeserializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Empty;

EmptyRenderingStrategyDeserializer::EmptyRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService) : DeserializerMixin(sceneService)
{
}

void EmptyRenderingStrategyDeserializer::_deserialize(
    const boost::json::value &value,
    deserializeMember deserializeMember,
    std::shared_ptr<IRenderingStrategy> root)
{
    auto serializedObject = value.as_object();

    auto position = _deserializePosition(serializedObject);
    auto rotation = _deserializeRotation(serializedObject);
    auto scale = _deserializeScale(serializedObject);

    auto empty = _sceneService->addEmpty(root);

    empty->setPosition(position);
    empty->setRotation(rotation);
    empty->setScale(scale);

    DeserializerMixin::_deserializeBase(value, deserializeMember, empty);
}