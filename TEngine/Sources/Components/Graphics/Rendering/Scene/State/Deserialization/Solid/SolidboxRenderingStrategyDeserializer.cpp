#include "SolidboxRenderingStrategyDeserializer.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::State::Deserialization::Solid;

SolidboxRenderingStrategyDeserializer::SolidboxRenderingStrategyDeserializer(std::shared_ptr<ISceneService> sceneService) : DeserializerMixin(sceneService)
{
}

void SolidboxRenderingStrategyDeserializer::_deserialize(
    const boost::json::value &value,
    deserializeMember deserializeMember,
    std::shared_ptr<IRenderingStrategy> root)
{
    auto serializedObject = value.as_object();

    auto position = _deserializePosition(serializedObject);
    auto rotation = _deserializeRotation(serializedObject);
    auto scale = _deserializeScale(serializedObject);

    auto solidbox = _sceneService->addSolidbox(root);

    solidbox->setPosition(position);
    solidbox->setRotation(rotation);
    solidbox->setScale(scale);

    DeserializerMixin::_deserializeBase(value, deserializeMember, solidbox);
}