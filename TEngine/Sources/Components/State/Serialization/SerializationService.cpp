#include "SerializationService.h"

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

boost::json::object SerializationService::_serialize(TypeInfoAware& value)
{
    auto typeIndex = value.getType();

    auto typeName = typeIndex.name();

    auto serializer = _serializers[typeIndex];
    return serializer->serialize(value, std::bind(&SerializationService::_serialize, this, std::placeholders::_1));
}