#include "DeserializationService.h"

#include <fstream>
#include <sstream>

using namespace TEngine::Components::State::Deserialization;

DeserializationService::DeserializationService(
    std::map<std::string, std::shared_ptr<IDeserializer>> deserializers,
    std::shared_ptr<Components::Core::Filesystem::IFileService> fileService)
    : _deserializers(deserializers),
      _fileService(fileService)
{
}

void DeserializationService::deserialize(const std::string &data, std::shared_ptr<TypeInfoAware> root)
{
    auto value = boost::json::parse(data);

    _deserialize(value, root);
}

void DeserializationService::deserializeFromFile(const std::string &path, std::shared_ptr<TypeInfoAware> root)
{
    auto sceneFileContent = _fileService->readAsString(path);

    deserialize(sceneFileContent, root);
}

void DeserializationService::_deserialize(const boost::json::value &data, std::shared_ptr<TypeInfoAware> root)
{
    auto type = data.at("type").as_string().c_str();

    auto deserializer = _deserializers[type];

    deserializer->deserialize(data, std::bind(&DeserializationService::_deserialize, this, std::placeholders::_1, std::placeholders::_2), root);
}