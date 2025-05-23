#include "SerializationService.h"

#include <fstream>

#include "boost/json.hpp"

using namespace TEngine::Components::State::Serialization;

SerializationService::SerializationService(std::map<std::type_index, std::shared_ptr<Serializers::ISerializer>> serializers)
    : _serializers(serializers)
{
}

std::string SerializationService::serialize(std::shared_ptr<Mixins::TypeInfoAware> value)
{
    auto valueObject = _serialize(*value);

    return boost::json::serialize(valueObject);
}

void SerializationService::serializeToFile(std::shared_ptr<Mixins::TypeInfoAware> value, const std::string& path) {
    auto sceneContent = serialize(value);

    std::ofstream sceneFile(path);

    sceneFile << sceneContent;

    sceneFile.close();
}

boost::json::object SerializationService::_serialize(TypeInfoAware& value)
{
    auto typeIndex = value.getType();

    auto serializer = _serializers[typeIndex];
    return serializer->serialize(value, std::bind(&SerializationService::_serialize, this, std::placeholders::_1));
}