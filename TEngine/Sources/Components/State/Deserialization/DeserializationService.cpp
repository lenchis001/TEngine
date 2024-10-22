#include "DeserializationService.h"

using namespace TEngine::Components::State::Deserialization;

DeserializationService::DeserializationService(std::map<std::string, std::shared_ptr<IDeserializer>> deserializers)
    : _deserializers(deserializers)
{
}

void DeserializationService::deserialize(const std::string& data)
{
    auto value = boost::json::parse(data);

    _deserialize(value);
}

void DeserializationService::_deserialize(const boost::json::value& data)
{
    auto type = data.at("type").as_string().c_str();

    auto deserializer = _deserializers[type];

    deserializer->deserialize(data, std::bind(&DeserializationService::_deserialize, this, std::placeholders::_1));
}