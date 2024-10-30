#ifndef TENGINE_IDESERIALIZER_H
#define TENGINE_IDESERIALIZER_H

#include <memory>
#include <functional>

#include "boost/json.hpp"

#include "Mixins/TypeInfoAware.h"
#include "Components/State/Serialization/ISerializationService.h"

namespace TEngine::Components::State::Deserialization::Deserializers
{
    typedef std::function<void(const boost::json::value &, std::shared_ptr<Mixins::TypeInfoAware>)> deserializeMember;

    class IDeserializer
    {
    public:
        virtual void deserialize(const boost::json::value &value, deserializeMember deserializeMember, std::shared_ptr<Mixins::TypeInfoAware> root) = 0;
        virtual ~IDeserializer() = default;
    };
}

#endif // TENGINE_IDESERIALIZER_H