#include "RenderingStrategyBaseSerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization;

boost::json::value RenderingStrategyBaseSerializer::_serialize(std::shared_ptr<RenderingStrategyBase> value, serializeMember serializeMember)
{
    boost::json::object obj;
    // obj["position"] = serializeMember(value.getPosition());
    // obj["rotation"] = serializeMember(value.getRotation());
    // obj["scale"] = serializeMember(value.getScale());

    boost::json::array children;
    for (auto &child : value->getChildren())
    {
        auto childObject = serializeMember(child);
        children.push_back(childObject);
    }
    obj["children"] = children;

    return obj;
}