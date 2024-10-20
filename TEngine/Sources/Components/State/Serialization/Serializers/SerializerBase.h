#ifndef TENGINE_SERIALIZERS_SERIALIZERBASE_H
#define TENGINE_SERIALIZERS_SERIALIZERBASE_H

#include "ISerializer.h"

using namespace TEngine::Mixins;

namespace TEngine::Components::State::Serialization::Serializers
{
    template <class T>
    class SerializerBase : public ISerializer
    {
    public:
        virtual boost::json::value serialize(TypeInfoAware& value, serializeMember serializeMember)
        {
            auto castedValue = static_cast<T*>(&value);

            return _serialize(*castedValue, serializeMember);
        }

    protected:
        virtual boost::json::value _serialize(T& value, serializeMember serializeMember) = 0;
    };
}

#endif // TENGINE_SERIALIZERS_SERIALIZERBASE_H