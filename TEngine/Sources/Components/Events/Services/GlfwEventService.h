#ifndef TENGINE_EVENT_SERVICE_H
#define TENGINE_EVENT_SERVICE_H

#ifdef TENGINE_USE_GLFW

#include "EventServiceBase.h"

#include "GLFW/glfw3.h"

#include "Mixins/ContextAwareMixin.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Events::Models;
using namespace TEngine::Mixins;

namespace TEngine::Components::Events::Services
{
    class GlfwEventService : public EventServiceBase, public ContextAwareMixin<GlfwEventService>
    {
    public:
        ~GlfwEventService() override;

        void initialize() override;

        void setCursorePosition(const Vector2di &value) override;
        void setCursorVisibility(bool isVisible) override;

    private:
        static void _keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void _cursorPosCallback(GLFWwindow *window, double xpos, double ypos);
        static void _mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void _scrollCallback(GLFWwindow *window, double xoffset, double yoffset);
        static void _charCallback(GLFWwindow *window, unsigned int codepoint);
        static void _cursorEnterCallback(GLFWwindow *window, int entered);
    };
}

#endif // TENGINE_USE_GLFW

#endif // TENGINE_EVENT_SERVICE_H