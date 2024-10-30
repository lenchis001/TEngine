#ifndef TENGINE_DESERIALIZERS_DESERIALIZERBASE_H
#define TENGINE_DESERIALIZERS_DESERIALIZERBASE_H

#include "IDeserializer.h"

using namespace TEngine::Mixins;

namespace TEngine::Components::State::Deserialization::Deserializers
{
    template <class T>
    class DeserializerBase : public IDeserializer
    {
    public:
        void deserialize(
            const boost::json::value &value,
            deserializeMember deserializeMember,
            std::shared_ptr<Mixins::TypeInfoAware> root) override
        {
            auto castedRoot = std::static_pointer_cast<T>(root);

            return _deserialize(value, deserializeMember, castedRoot);
        }

    protected:
        virtual void _deserialize(const boost::json::value& value, deserializeMember serializeMember, std::shared_ptr<T> root) = 0;
    };
}

#endif // TENGINE_DESERIALIZERS_DESERIALIZERBASE_H