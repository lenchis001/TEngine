#ifndef TENGINE_I_EVENT_SERVICE_H
#define TENGINE_I_EVENT_SERVICE_H

#include <functional>

#include "Components/Graphics/Models/Vector2d.h"

#include "Components/Events/Models/KeyboardKeys.h"

typedef std::function<bool(bool)> KeyboardEventHandler;
typedef std::function<bool(float, float)> MousePositionEventHandler;

namespace TEngine::Components::Events::Services
{
    class IEventService
    {
    public:
        virtual ~IEventService() = default;

        virtual void initialize() = 0;

        virtual void registerHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler) = 0;
        virtual void registerHandler(const MousePositionEventHandler &handler) = 0;

        virtual void unregisterHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler) = 0;
        virtual void unregisterHandler(const MousePositionEventHandler &handler) = 0;

        virtual void setCursorePosition(const Graphics::Models::Vector2di& value) = 0;
        virtual void setCursorVisibility(bool isVisible) = 0;
    };
}

#endif // TENGINE_I_EVENT_SERVICE_H