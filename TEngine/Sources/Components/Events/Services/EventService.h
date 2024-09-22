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

        void registerHandler(KeyboardKeys key, const KeyboardEventHandler &handler) override;
        void registerHandler(const MousePositionEventHandler &handler) override;

        void unregisterHandler(KeyboardKeys key, const KeyboardEventHandler &handler) override;
        void unregisterHandler(const MousePositionEventHandler &handler) override;

        void setCursorePosition(const Vector2di& value) override;
        void setCursorVisibility(bool isVisible) override;

    private:
        static void _keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void _mousePosCallback(GLFWwindow *window, double xpos, double ypos);

        std::unordered_map<KeyboardKeys, std::vector<KeyboardEventHandler>> _keyboardHandlers;
        std::vector<MousePositionEventHandler> _mouseHandlers;
    };
}

#endif // TENGINE_EVENT_SERVICE_H