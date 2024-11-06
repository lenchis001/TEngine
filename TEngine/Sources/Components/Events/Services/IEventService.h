#ifndef TENGINE_I_EVENT_SERVICE_H
#define TENGINE_I_EVENT_SERVICE_H

#include <functional>

#include "Components/Graphics/Models/Vector2d.h"

#include "Components/Events/Models/KeyboardKeys.h"
#include "Components/Events/Models/KeyStates.h"
#include "Components/Events/Models/MouseButtons.h"

namespace TEngine::Components::Events::Services
{
    typedef std::function<bool(Models::KeyboardKeys, int, Models::KeyStates, int)> KeyboardEventHandler;
    typedef std::function<bool(int, int)> CursorMoveEventHandler;
    typedef std::function<bool(Models::MouseButtons, Models::KeyStates, int)> MouseButtonEventHandler;
    typedef std::function<bool(float, float)> ScrollEventHandler;
    typedef std::function<bool(unsigned int)> CharEventHandler;
    typedef std::function<bool(bool)> CursorEnterEventHandler;

    class IEventService
    {
    public:
        virtual ~IEventService() = default;

        virtual void initialize() = 0;

        virtual void registerKeyHandler(const KeyboardEventHandler &handler) = 0;
        virtual void unregisterKeyHandler(const KeyboardEventHandler &handler) = 0;
        virtual void fireKeyHandler(Models::KeyboardKeys key, int scancode, Models::KeyStates action, int mods) = 0;

        virtual void registerCursorMoveHandler(const CursorMoveEventHandler &handler) = 0;
        virtual void unregisterCursorMoveHandler(const CursorMoveEventHandler &handler) = 0;
        virtual void fireCursorMoveHandler(int xpos, int ypos) = 0;

        virtual void registerMouseButtonHandler(const MouseButtonEventHandler &handler) = 0;
        virtual void unregisterMouseButtonHandler(const MouseButtonEventHandler &handler) = 0;
        virtual void fireMouseButtonHandler(Models::MouseButtons button, Models::KeyStates action, int mods) = 0;

        virtual void registerScrollHandler(const ScrollEventHandler &handler) = 0;
        virtual void unregisterScrollHandler(const ScrollEventHandler &handler) = 0;
        virtual void fireScrollHandler(float xoffset, float yoffset) = 0;

        virtual void registerCharHandler(const CharEventHandler &handler) = 0;
        virtual void unregisterCharHandler(const CharEventHandler &handler) = 0;
        virtual void fireCharHandler(unsigned int codepoint) = 0;

        virtual void registerCursorEnterHandler(const CursorEnterEventHandler &handler) = 0;
        virtual void unregisterCursorEnterHandler(const CursorEnterEventHandler &handler) = 0;
        virtual void fireCursorEnterHandler(bool entered) = 0;

        virtual void setCursorePosition(const Graphics::Models::Vector2di &value) = 0;
        virtual void setCursorVisibility(bool isVisible) = 0;
    };
}

#endif // TENGINE_I_EVENT_SERVICE_H