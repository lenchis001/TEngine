#include "IDeserializationService.h"

#include <map>

#include "boost/json.hpp"

#include "Deserializers/IDeserializer.h"

using namespace TEngine::Components::State::Deserialization::Deserializers;

namespace TEngine::Components::State::Deserialization
{
    class DeserializationService : public IDeserializationService
    {
    public:
        DeserializationService(std::map<std::string, std::shared_ptr<IDeserializer>> serializers);

        void deserialize(const std::string& data) override;

    private:
        void _deserialize(const boost::json::value& data);

        std::map<std::string, std::shared_ptr<IDeserializer>> _deserializers;
    };
}