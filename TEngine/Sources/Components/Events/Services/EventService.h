#ifndef TENGINE_EVENT_SERVICE_H
#define TENGINE_EVENT_SERVICE_H

#include "IEventService.h"

#include "unordered_map"
#include "vector"

#include "GLFW/glfw3.h"

#include "Mixins/ContextAwareMixin.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Events::Models;
using namespace TEngine::Mixins;

namespace TEngine::Components::Events::Services
{
    class EventService : public IEventService, public ContextAwareMixin<EventService>
    {
    public:
        EventService() = default;
        ~EventService() override;

        void initialize() override;

        void registerKeyHandler(KeyboardKeys key, const KeyboardEventHandler &handler) override;
        void unregisterKeyHandler(KeyboardKeys key, const KeyboardEventHandler &handler) override;

        void registerCursorMoveHandler(const CursorMoveEventHandler &handler) override;
        void unregisterCursorMoveHandler(const CursorMoveEventHandler &handler) override;

        void registerMouseButtonHandler(const MouseButtonEventHandler &handler) override;
        void unregisterMouseButtonHandler(const MouseButtonEventHandler &handler) override;

        void setCursorePosition(const Vector2di& value) override;
        void setCursorVisibility(bool isVisible) override;

    private:
        static void _keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void _cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
        static void _mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

        std::unordered_map<KeyboardKeys, std::vector<KeyboardEventHandler>> _keyboardHandlers;
        std::vector<CursorMoveEventHandler> _cursorMoveHandlers;
        std::vector<MouseButtonEventHandler> _mouseButtonHandlers;
    };
}

#endif // TENGINE_EVENT_SERVICE_H