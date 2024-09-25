#ifndef TENGINE_I_EVENT_SERVICE_H
#define TENGINE_I_EVENT_SERVICE_H

#include <functional>

#include "Components/Graphics/Models/Vector2d.h"

#include "Components/Events/Models/KeyboardKeys.h"

typedef std::function<bool(int, int, int, int)> KeyboardEventHandler;
typedef std::function<bool(float, float)> CursorMoveEventHandler;
typedef std::function<bool(int, int, int)> MouseButtonEventHandler;
typedef std::function<bool(float, float)> ScrollEventHandler;
typedef std::function<bool(unsigned int)> CharEventHandler;

namespace TEngine::Components::Events::Services
{
    class IEventService
    {
    public:
        virtual ~IEventService() = default;

        virtual void initialize() = 0;

        virtual void registerKeyHandler(const KeyboardEventHandler &handler) = 0;
        virtual void unregisterKeyHandler(const KeyboardEventHandler &handler) = 0;

        virtual void registerCursorMoveHandler(const CursorMoveEventHandler &handler) = 0;
        virtual void unregisterCursorMoveHandler(const CursorMoveEventHandler &handler) = 0;

        virtual void registerMouseButtonHandler(const MouseButtonEventHandler &handler) = 0;
        virtual void unregisterMouseButtonHandler(const MouseButtonEventHandler &handler) = 0;

        virtual void registerScrollHandler(const ScrollEventHandler &handler) = 0;
        virtual void unregisterScrollHandler(const ScrollEventHandler &handler) = 0;

        virtual void registerCharHandler(const CharEventHandler &handler) = 0;
        virtual void unregisterCharHandler(const CharEventHandler &handler) = 0;

        virtual void setCursorePosition(const Graphics::Models::Vector2di& value) = 0;
        virtual void setCursorVisibility(bool isVisible) = 0;
    };
}

#endif // TENGINE_I_EVENT_SERVICE_H