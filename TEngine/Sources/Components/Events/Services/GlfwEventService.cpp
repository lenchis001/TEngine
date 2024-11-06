#include "GlfwEventService.h"

using namespace TEngine::Components::Events::Services;

GlfwEventService::~GlfwEventService()
{
    assert(_keyboardHandlers.empty() && "Not all keyboard handlers were unregistered");
    assert(_cursorMoveHandlers.empty() && "Not all mouse handlers were unregistered");
    assert(_mouseButtonHandlers.empty() && "Not all mouse button handlers were unregistered");
    assert(_scrollHandlers.empty() && "Not all scroll handlers were unregistered");
    assert(_charHandlers.empty() && "Not all char handlers were unregistered");
}

void GlfwEventService::initialize()
{
    setContext(this);

    glfwSetKeyCallback(glfwGetCurrentContext(), &GlfwEventService::_keyCallback);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), &GlfwEventService::_cursorPosCallback);
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), &GlfwEventService::_mouseButtonCallback);
    glfwSetScrollCallback(glfwGetCurrentContext(), &GlfwEventService::_scrollCallback);
    glfwSetCharCallback(glfwGetCurrentContext(), &GlfwEventService::_charCallback);
    glfwSetCursorEnterCallback(glfwGetCurrentContext(), &GlfwEventService::_cursorEnterCallback);
}

void GlfwEventService::setCursorePosition(const Vector2di &value)
{
    glfwSetCursorPos(glfwGetCurrentContext(), value.getX(), value.getY());
}

void GlfwEventService::setCursorVisibility(bool isVisible)
{
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, isVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void GlfwEventService::_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto that = getContext();

    that->fireKeyHandler(static_cast<KeyboardKeys>(key), scancode, static_cast<KeyStates>(action), mods);
}

void GlfwEventService::_cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    auto that = getContext();

    that->fireCursorMoveHandler(xpos, ypos);
}

void GlfwEventService::_mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    auto that = getContext();

    that->fireMouseButtonHandler(static_cast<MouseButtons>(button), static_cast<KeyStates>(action), mods);
}

void GlfwEventService::_scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    auto that = getContext();

    that->fireScrollHandler(xoffset, yoffset);
}

void GlfwEventService::_charCallback(GLFWwindow *window, unsigned int codepoint)
{
    auto that = getContext();

    that->fireCharHandler(codepoint);
}

void GlfwEventService::_cursorEnterCallback(GLFWwindow *window, int entered)
{
    auto that = getContext();

    that->fireCursorEnterHandler(entered);
}
