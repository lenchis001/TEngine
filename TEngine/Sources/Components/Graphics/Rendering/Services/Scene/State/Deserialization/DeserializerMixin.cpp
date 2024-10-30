#include "DeserializerMixin.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::State::Deserialization;

DeserializerMixin::DeserializerMixin(std::shared_ptr<ISceneService> sceneService) : _sceneService(sceneService)
{
}

void DeserializerMixin::_deserializeBase(const boost::json::value &value, deserializeMember deserializeMember, std::shared_ptr<IRenderingStrategy> root)
{
    auto &object = value.as_object();

    for (auto &child : object.at("children").as_array())
    {
        deserializeMember(child, root);
    }
}

Vector3df DeserializerMixin::_deserializePosition(const boost::json::object &value)
{
    auto serializedObject = value.at("position").as_object();

    return _deserializeVecror3d<float>(serializedObject);
}

Vector3df DeserializerMixin::_deserializeRotation(const boost::json::object &value)
{
    auto serializedObject = value.at("rotation").as_object();

    return _deserializeVecror3d<float>(serializedObject);
}

Vector3df DeserializerMixin::_deserializeScale(const boost::json::object &value)
{
    auto serializedObject = value.at("scale").as_object();

    return _deserializeVecror3d<float>(serializedObject);
}

PhysicsFlags DeserializerMixin::_toPhysicsFlag(const std::string &value)
{
    if (value == "dynamic")
    {
        return PhysicsFlags::DYNAMIC;
    }
    else if (value == "static")
    {
        return PhysicsFlags::STATIC;
    }
    else if (value == "none")
    {
        return PhysicsFlags::NONE;
    }
    else
    {
        throw std::runtime_error("Unknown physics flag string representation");
    }
}