#ifndef TENGINE_ISERIALIZER_H
#define TENGINE_ISERIALIZER_H

#include <memory>
#include <functional>

#include "boost/json.hpp"

#include "Components/State/Serialization/ISerializationService.h"

namespace TEngine::Components::State::Serialization::Serializers
{
    typedef std::function<boost::json::value(std::shared_ptr<Mixins::TypeInfoAware>)> serializeMember;

    class ISerializer
    {
    public:
        virtual boost::json::value serialize(std::shared_ptr<Mixins::TypeInfoAware> value, serializeMember serializeMember) = 0;
        virtual ~ISerializer() = default;
    };
}

#endif // TENGINE_ISERIALIZER_H