#ifndef TENGINE_EVENT_SERVICE_H
#define TENGINE_EVENT_SERVICE_H

#include "IEventService.h"

#include "unordered_map"
#include "vector"
#include <algorithm>

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

        void registerKeyHandler(const KeyboardEventHandler &handler) override;
        void unregisterKeyHandler(const KeyboardEventHandler &handler) override;

        void registerCursorMoveHandler(const CursorMoveEventHandler &handler) override;
        void unregisterCursorMoveHandler(const CursorMoveEventHandler &handler) override;

        void registerMouseButtonHandler(const MouseButtonEventHandler &handler) override;
        void unregisterMouseButtonHandler(const MouseButtonEventHandler &handler) override;

        void registerScrollHandler(const ScrollEventHandler &handler) override;
        void unregisterScrollHandler(const ScrollEventHandler &handler) override;

        void registerCharHandler(const CharEventHandler &handler) override;
        void unregisterCharHandler(const CharEventHandler &handler) override;

        void setCursorePosition(const Vector2di &value) override;
        void setCursorVisibility(bool isVisible) override;

    private:
        static void _keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void _cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
        static void _mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void _scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
        static void _charCallback(GLFWwindow *window, unsigned int codepoint);

        template <class T>
        static void removeEventHandler(std::vector<T> &handlers, const T &handler)
        {
            auto handlersSize = handlers.size();

            handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&handler](const T &h)
                                          { return h.target_type() == handler.target_type() && h.template target<T>() == handler.template target<T>(); }),
                           handlers.end());

            assert((handlersSize - 1) == handlers.size() && "Handler was not found");
        }

        std::vector<KeyboardEventHandler> _keyboardHandlers;
        std::vector<CursorMoveEventHandler> _cursorMoveHandlers;
        std::vector<MouseButtonEventHandler> _mouseButtonHandlers;
        std::vector<ScrollEventHandler> _scrollHandlers;
        std::vector<CharEventHandler> _charHandlers;
    };
}

#endif // TENGINE_EVENT_SERVICE_H