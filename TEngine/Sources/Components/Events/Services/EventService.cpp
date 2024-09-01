#include "EventService.h"

#include "cassert"
#include "algorithm"

using namespace TEngine::Components::Events::Services;

#define ARE_KEYBOARD_HANDLERS_EQUAL(h1, h2) (h1.target_type() == h2.target_type() && h1.target<KeyboardEventHandler>() == h2.target<KeyboardEventHandler>())
#define ARE_MOUSE_HANDLERS_EQUAL(h1, h2) (h1.target_type() == h2.target_type() && h1.target<MousePositionEventHandler>() == h2.target<MousePositionEventHandler>())

EventService::~EventService()
{
    for (auto &handlers : _keyboardHandlers)
    {
        assert(handlers.second.empty() && "Not all keyboard handlers were unregistered");
    }

    assert(_mouseHandlers.empty() && "Not all mouse handlers were unregistered");
}

void EventService::initialize()
{
    setContext(this);

    glfwSetKeyCallback(glfwGetCurrentContext(), &EventService::_keyCallback);
    glfwSetCursorPosCallback(glfwGetCurrentContext(), &EventService::_mousePosCallback);
}

void EventService::registerHandler(KeyboardKeys key, const KeyboardEventHandler &handler)
{
    _keyboardHandlers[key].push_back(handler);
}

void EventService::registerHandler(const MousePositionEventHandler &handler)
{
    _mouseHandlers.push_back(handler);
}

void EventService::unregisterHandler(KeyboardKeys key, const KeyboardEventHandler &handler)
{
    if (_keyboardHandlers.find(key) != _keyboardHandlers.end())
    {
        auto &handlers = _keyboardHandlers[key];

        auto handlersSize = handlers.size();

        handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&handler](const KeyboardEventHandler &h)
                                      { return ARE_KEYBOARD_HANDLERS_EQUAL(h, handler); }),
                       handlers.end());

        assert((handlersSize -1) == handlers.size() && "Handler was not found");
    }
}

void EventService::unregisterHandler(const MousePositionEventHandler &handler)
{
    auto handlersSize = _mouseHandlers.size();

    _mouseHandlers.erase(std::remove_if(_mouseHandlers.begin(), _mouseHandlers.end(), [&handler](const MousePositionEventHandler &h)
                                        { return ARE_MOUSE_HANDLERS_EQUAL(h, handler); }),
                         _mouseHandlers.end());

    assert((handlersSize -1) == _mouseHandlers.size() && "Handler was not found");
}

void EventService::setCursorePosition(float x, float y)
{
    glfwSetCursorPos(glfwGetCurrentContext(), x, y);
}

void EventService::_keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    auto that = getContext();

    if (that->_keyboardHandlers.find(static_cast<KeyboardKeys>(key)) != that->_keyboardHandlers.end())
    {
        for (auto &handler : that->_keyboardHandlers[static_cast<KeyboardKeys>(key)])
        {
            if (handler(action == GLFW_PRESS || action == GLFW_REPEAT))
            {
                break;
            }
        }
    }
}

void EventService::_mousePosCallback(GLFWwindow *window, double xpos, double ypos)
{
    auto that = getContext();

    for (auto &handler : that->_mouseHandlers)
    {
        if (handler(xpos, ypos))
        {
            break;
        }
    }
}