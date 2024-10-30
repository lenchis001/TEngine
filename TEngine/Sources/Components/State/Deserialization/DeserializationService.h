#include "IDeserializationService.h"

#include <map>

#include "boost/json.hpp"

#include "Deserializers/IDeserializer.h"

using namespace TEngine::Mixins;
using namespace TEngine::Components::State::Deserialization::Deserializers;

namespace TEngine::Components::State::Deserialization
{
    class DeserializationService : public IDeserializationService
    {
    public:
        DeserializationService(std::map<std::string, std::shared_ptr<IDeserializer>> serializers);

        void deserialize(const std::string& data, std::shared_ptr<TypeInfoAware> root = nullptr) override;

        void deserializeFromFile(const std::string& path, std::shared_ptr<TypeInfoAware> root = nullptr) override;

    private:
        void _deserialize(const boost::json::value& data, std::shared_ptr<TypeInfoAware> root);

        std::map<std::string, std::shared_ptr<IDeserializer>> _deserializers;
    };
}