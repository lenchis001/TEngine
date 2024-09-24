#include "EventService.h"

#include "cassert"
#include "algorithm"

using namespace TEngine::Components::Events::Services;

EventService::~EventService()
{
    assert(_keyboardHandlers.empty() && "Not all keyboard handlers were unregistered");
    assert(_cursorMoveHandlers.empty() && "Not all mouse handlers were unregistered");
    assert(_mouseButtonHandlers.empty() && "Not all mouse button handlers were unregistered");
    assert(_scrollHandlers.empty() && "Not all scroll handlers were unregistered");
    assert(_charHandlers.empty() && "Not all char handlers were unregistered");
}

void EventService::initialize()
{
    setContext(this);

    glfwSetKeyCallback(glfwGetCurrentContext(), &EventService::_keyCallback);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), &EventService::_cursorPosCallback);
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), &EventService::_mouseButtonCallback);
    glfwSetScrollCallback(glfwGetCurrentContext(), &EventService::_scrollCallback);
    glfwSetCharCallback(glfwGetCurrentContext(), &EventService::_charCallback);
}

void EventService::registerKeyHandler(const KeyboardEventHandler &handler)
{
    _keyboardHandlers.push_back(handler);
}

void EventService::unregisterKeyHandler(const KeyboardEventHandler &handler)
{
    removeEventHandler(_keyboardHandlers, handler);
}

void EventService::registerCursorMoveHandler(const CursorMoveEventHandler &handler)
{
    _cursorMoveHandlers.push_back(handler);
}

void EventService::unregisterCursorMoveHandler(const CursorMoveEventHandler &handler)
{
    removeEventHandler(_cursorMoveHandlers, handler);
}

void EventService::registerMouseButtonHandler(const MouseButtonEventHandler &handler)
{
    _mouseButtonHandlers.push_back(handler);
}

void EventService::unregisterMouseButtonHandler(const MouseButtonEventHandler &handler)
{
    removeEventHandler(_mouseButtonHandlers, handler);
}

void EventService::registerScrollHandler(const ScrollEventHandler &handler)
{
    _scrollHandlers.push_back(handler);
}

void EventService::unregisterScrollHandler(const ScrollEventHandler &handler)
{
    removeEventHandler(_scrollHandlers, handler);
}

void EventService::registerCharHandler(const CharEventHandler &handler)
{
    _charHandlers.push_back(handler);
}

void EventService::unregisterCharHandler(const CharEventHandler &handler)
{
    removeEventHandler(_charHandlers, handler);
}

void EventService::setCursorePosition(const Vector2di &value)
{
    glfwSetCursorPos(glfwGetCurrentContext(), value.getX(), value.getY());
}

void EventService::setCursorVisibility(bool isVisible)
{
    glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, isVisible ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void EventService::_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto that = getContext();

    for (auto &handler : that->_keyboardHandlers)
    {
        if (handler(key, scancode, action, mods))
        {
            break;
        }
    }
}

void EventService::_cursorPosCallback(GLFWwindow *window, double xpos, double ypos)
{
    auto that = getContext();

    for (auto &handler : that->_cursorMoveHandlers)
    {
        if (handler(xpos, ypos))
        {
            break;
        }
    }
}

void EventService::_mouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    auto that = getContext();

    for (auto &handler : that->_mouseButtonHandlers)
    {
        if (handler(button, action, mods))
        {
            break;
        }
    }
}

void EventService::_scrollCallback(GLFWwindow *window, double xoffset, double yoffset)
{
    auto that = getContext();

    for (auto &handler : that->_scrollHandlers)
    {
        if (handler(xoffset, yoffset))
        {
            break;
        }
    }
}

void EventService::_charCallback(GLFWwindow *window, unsigned int codepoint)
{
    auto that = getContext();

    for (auto &handler : that->_charHandlers)
    {
        if (handler(codepoint))
        {
            break;
        }
    }
}
