#include "EventService.h"

#include "cassert"
#include "algorithm"

using namespace TEngine::Components::Events::Services;

#define ARE_KEYBOARD_HANDLERS_EQUAL(h1, h2) (h1.target_type() == h2.target_type() && h1.target<KeyboardEventHandler>() == h2.target<KeyboardEventHandler>())
#define ARE_MOUSE_HANDLERS_EQUAL(h1, h2) (h1.target_type() == h2.target_type() && h1.target<CursorMoveEventHandler>() == h2.target<CursorMoveEventHandler>())

EventService::~EventService()
{
    for (auto &handlers : _keyboardHandlers)
    {
        assert(handlers.second.empty() && "Not all keyboard handlers were unregistered");
    }

    assert(_cursorMoveHandlers.empty() && "Not all mouse handlers were unregistered");
}

void EventService::initialize()
{
    setContext(this);

    glfwSetKeyCallback(glfwGetCurrentContext(), &EventService::_keyCallback);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), &EventService::_cursorPosCallback);
    glfwSetMouseButtonCallback(glfwGetCurrentContext(), &EventService::_mouseButtonCallback);
}

void EventService::registerKeyHandler(KeyboardKeys key, const KeyboardEventHandler &handler)
{
    _keyboardHandlers[key].push_back(handler);
}

void EventService::unregisterKeyHandler(KeyboardKeys key, const KeyboardEventHandler &handler)
{
    if (_keyboardHandlers.find(key) != _keyboardHandlers.end())
    {
        auto &handlers = _keyboardHandlers[key];

        auto handlersSize = handlers.size();

        handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&handler](const KeyboardEventHandler &h)
                                      { return ARE_KEYBOARD_HANDLERS_EQUAL(h, handler); }),
                       handlers.end());

        assert((handlersSize - 1) == handlers.size() && "Handler was not found");
    }
}

void EventService::registerCursorMoveHandler(const CursorMoveEventHandler &handler)
{
    _cursorMoveHandlers.push_back(handler);
}

void EventService::unregisterCursorMoveHandler(const CursorMoveEventHandler &handler)
{
    auto handlersSize = _cursorMoveHandlers.size();

    _cursorMoveHandlers.erase(std::remove_if(_cursorMoveHandlers.begin(), _cursorMoveHandlers.end(), [&handler](const CursorMoveEventHandler &h)
                                        { return ARE_MOUSE_HANDLERS_EQUAL(h, handler); }),
                         _cursorMoveHandlers.end());

    assert((handlersSize - 1) == _cursorMoveHandlers.size() && "Handler was not found");
}

void EventService::registerMouseButtonHandler(const MouseButtonEventHandler &handler)
{
    _mouseButtonHandlers.push_back(handler);
}

void EventService::unregisterMouseButtonHandler(const MouseButtonEventHandler &handler)
{
    auto handlersSize = _mouseButtonHandlers.size();

    _mouseButtonHandlers.erase(std::remove_if(_mouseButtonHandlers.begin(), _mouseButtonHandlers.end(), [&handler](const MouseButtonEventHandler &h)
                                        { return h.target_type() == handler.target_type() && h.target<MouseButtonEventHandler>() == handler.target<MouseButtonEventHandler>(); }),
                         _mouseButtonHandlers.end());

    assert((handlersSize - 1) == _mouseButtonHandlers.size() && "Handler was not found");
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

    for (auto &handler : that->_keyboardHandlers[static_cast<KeyboardKeys>(key)])
    {
        if (handler(action == GLFW_PRESS || action == GLFW_REPEAT))
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