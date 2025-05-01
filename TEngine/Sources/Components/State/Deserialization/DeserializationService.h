#include "IDeserializationService.h"

#include <map>
#include <memory>

#include "boost/json.hpp"

#include "Components/Core/Filesystem/IFileService.h"

#include "Deserializers/IDeserializer.h"

using namespace TEngine::Mixins;
using namespace TEngine::Components::State::Deserialization::Deserializers;

namespace TEngine::Components::State::Deserialization
{
    class DeserializationService : public IDeserializationService
    {
    public:
        DeserializationService(
            std::map<std::string, std::shared_ptr<IDeserializer>> serializers,
            std::shared_ptr<Components::Core::Filesystem::IFileService> fileService);

        void deserialize(const std::string &data, std::shared_ptr<TypeInfoAware> root = nullptr) override;

        void deserializeFromFile(const std::string &path, std::shared_ptr<TypeInfoAware> root = nullptr) override;

    private:
        void _deserialize(const boost::json::value &data, std::shared_ptr<TypeInfoAware> root);

        std::map<std::string, std::shared_ptr<IDeserializer>> _deserializers;
        std::shared_ptr<Components::Core::Filesystem::IFileService> _fileService;
    };
}