#ifndef TENGINE_I_EVENT_SERVICE_H
#define TENGINE_I_EVENT_SERVICE_H

#include <functional>

#include "Components/Graphics/Models/Vector2d.h"

#include "Components/Events/Models/KeyboardKeys.h"

typedef std::function<bool(bool)> KeyboardEventHandler;
typedef std::function<bool(float, float)> CursorMoveEventHandler;
typedef std::function<bool(int, int, int)> MouseButtonEventHandler;

namespace TEngine::Components::Events::Services
{
    class IEventService
    {
    public:
        virtual ~IEventService() = default;

        virtual void initialize() = 0;

        virtual void registerKeyHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler) = 0;
        virtual void unregisterKeyHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler) = 0;

        virtual void registerCursorMoveHandler(const CursorMoveEventHandler &handler) = 0;
        virtual void unregisterCursorMoveHandler(const CursorMoveEventHandler &handler) = 0;

        virtual void registerMouseButtonHandler(const MouseButtonEventHandler &handler) = 0;
        virtual void unregisterMouseButtonHandler(const MouseButtonEventHandler &handler) = 0;

        virtual void setCursorePosition(const Graphics::Models::Vector2di& value) = 0;
        virtual void setCursorVisibility(bool isVisible) = 0;
    };
}

#endif // TENGINE_I_EVENT_SERVICE_H