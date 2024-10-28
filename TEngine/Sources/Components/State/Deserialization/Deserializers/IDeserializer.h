#ifndef TENGINE_IDESERIALIZER_H
#define TENGINE_IDESERIALIZER_H

#include <memory>
#include <functional>

#include "boost/json.hpp"

#include "Components/State/Serialization/ISerializationService.h"

namespace TEngine::Components::State::Deserialization::Deserializers
{
    typedef std::function<void(const boost::json::value &, std::shared_ptr<TypeInfoAware>)> deserializeMember;

    class IDeserializer
    {
    public:
        virtual void deserialize(const boost::json::value &value, deserializeMember serializeMember) = 0;
        virtual ~IDeserializer() = default;
    };
}

#endif // TENGINE_IDESERIALIZER_H