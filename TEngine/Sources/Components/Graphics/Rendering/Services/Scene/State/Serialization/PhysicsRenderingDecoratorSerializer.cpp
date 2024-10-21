#include "PhysicsRenderingDecoratorSerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization;

boost::json::object PhysicsRenderingDecoratorSerializer::_serialize(
    PhysicsRenderingDecorator& value,
    serializeMember serializeMember)
{
    boost::json::object result;
    
    auto physicsFlags = value.getPhysicsFlags();
    result["physicsFlags"] = (int)physicsFlags;

    auto internalStrategy = value.getInternalStrategy();
    auto internalSerialized = serializeMember(*internalStrategy);

    for (auto& [key, value] : internalSerialized)
    {
        result[key] = value;
    }

    return result;
}