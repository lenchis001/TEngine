#ifndef TENGINE_DESERIALIZERS_DESERIALIZERBASE_H
#define TENGINE_DESERIALIZERS_DESERIALIZERBASE_H

#include "ISerializer.h"

using namespace TEngine::Mixins;

namespace TEngine::Components::State::Serialization::Serializers
{
    template <class T>
    class DeserializerBase : public ISerializer
    {
    public:
        virtual boost::json::object serialize(TypeInfoAware& value, deserializeMember serializeMember)
        {
            auto castedValue = static_cast<T*>(&value);

            return _deserialize(*castedValue, serializeMember);
        }

    protected:
        virtual boost::json::object _deserialize(T& value, serializeMember serializeMember) = 0;
    };
}

#endif // TENGINE_DESERIALIZERS_DESERIALIZERBASE_H