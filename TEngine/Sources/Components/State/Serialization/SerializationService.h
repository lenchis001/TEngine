#ifndef TENGINE_SERIALIZATIONSERVICE_H
#define TENGINE_SERIALIZATIONSERVICE_H

#include "ISerializationService.h"

#include <map>
#include <typeindex>
#include <memory>

#include "Serializers/ISerializer.h"

using namespace TEngine::Mixins;
using namespace TEngine::Components::State::Serialization::Serializers;

namespace TEngine::Components::State::Serialization
{
    class SerializationService : public ISerializationService
    {
    public:
        SerializationService(std::map<std::type_index, std::shared_ptr<ISerializer>> serializers);

        std::string serialize(std::shared_ptr<TypeInfoAware> value) override;
    private:
        boost::json::value _serialize(TypeInfoAware& value);

        std::map<std::type_index, std::shared_ptr<ISerializer>> _serializers;
    };
}

#endif // TENGINE_SERIALIZATIONSERVICE_H