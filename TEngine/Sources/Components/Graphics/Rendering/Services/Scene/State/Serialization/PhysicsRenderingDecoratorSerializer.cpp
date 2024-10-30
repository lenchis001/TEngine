#include "PhysicsRenderingDecoratorSerializer.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Serialization;

boost::json::object PhysicsRenderingDecoratorSerializer::_serialize(
    PhysicsRenderingDecorator& value,
    serializeMember serializeMember)
{
    boost::json::object result;
    
    auto physicsFlags = value.getPhysicsFlags();
    result["physicsFlags"] = _toString(physicsFlags);

    auto internalStrategy = value.getInternalStrategy();
    auto internalSerialized = serializeMember(*internalStrategy);

    for (auto& [key, value] : internalSerialized)
    {
        result[key] = value;
    }

    return result;
}

std::string PhysicsRenderingDecoratorSerializer::_toString(PhysicsFlags flag)
{
    switch (flag)
    {
    case PhysicsFlags::DYNAMIC:
        return "dynamic";
    case PhysicsFlags::STATIC:
        return "static";
    case PhysicsFlags::NONE:
        return "none";
    default:
        throw std::runtime_error("Unknown physics flag");
    }
}