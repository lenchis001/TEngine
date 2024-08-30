#ifndef TENGINE_I_EVENT_SERVICE_H
#define TENGINE_I_EVENT_SERVICE_H

#include "functional"

#include "Components/Events/Models/KeyboardKeys.h"

typedef std::function<bool(bool)> KeyboardEventHandler;

namespace TEngine::Components::Events::Services
{
    class IEventService
    {
    public:
        virtual ~IEventService() = default;

        virtual void initialize() = 0;

        virtual void registerHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler) = 0;
    };
}

#endif // TENGINE_I_EVENT_SERVICE_H