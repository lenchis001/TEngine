#ifndef TENGINE_ISERIALIZATIONSERVICE_H
#define TENGINE_ISERIALIZATIONSERVICE_H

#include <memory>
#include <string>

#include "Mixins/TypeInfoAware.h"

namespace TEngine::Components::State::Serialization
{
    class ISerializationService : public std::enable_shared_from_this<ISerializationService>
    {
    public:
        virtual std::string serialize(std::shared_ptr<Mixins::TypeInfoAware> value) = 0;

        virtual void serializeToFile(std::shared_ptr<Mixins::TypeInfoAware> value, const std::string& path) = 0;

        virtual ~ISerializationService() = default;
    };
}

#endif // TENGINE_ISERIALIZATIONSERVICE_H