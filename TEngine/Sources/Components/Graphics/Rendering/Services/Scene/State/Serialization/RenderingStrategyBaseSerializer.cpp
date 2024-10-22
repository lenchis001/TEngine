#include "RenderingStrategyBaseSerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization;

RenderingStrategyBaseSerializer::RenderingStrategyBaseSerializer()
{
    setType("base");
}

boost::json::object RenderingStrategyBaseSerializer::_serialize(RenderingStrategyBase& value, serializeMember serializeMember)
{
    boost::json::object obj;

    const auto& position = value.getPosition();
    obj["position"] = _serializeVecror3d(position);
    const auto& rotation = value.getRotation();
    obj["rotation"] = _serializeVecror3d(rotation);
    const auto& scale = value.getScale();
    obj["scale"] = _serializeVecror3d(scale);

    obj["type"] = _type;

    boost::json::array children;
    for (auto &child : value.getChildren())
    {
        auto childObject = serializeMember(*child);
        children.push_back(childObject);
    }
    obj["children"] = children;

    return obj;
}

void RenderingStrategyBaseSerializer::setType(const std::string &type)
{
    _type = type;
}