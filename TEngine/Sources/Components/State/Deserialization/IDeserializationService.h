#ifndef TENGINE_IDESERIALIZATIONSERVICE_H
#define TENGINE_IDESERIALIZATIONSERVICE_H

#include <memory>
#include <string>

#include "Mixins/TypeInfoAware.h"

namespace TEngine::Components::State::Deserialization
{
    class IDeserializationService : public std::enable_shared_from_this<IDeserializationService>
    {
    public:
        virtual void deserialize(const std::string& data, std::shared_ptr<Mixins::TypeInfoAware> root = nullptr) = 0;

        virtual void deserializeFromFile(const std::string& path, std::shared_ptr<Mixins::TypeInfoAware> root = nullptr) = 0;

        virtual ~IDeserializationService() = default;
    };
}

#endif // TENGINE_IDESERIALIZATIONSERVICE_H