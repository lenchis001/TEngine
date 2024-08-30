#include "EventService.h"

using namespace TEngine::Components::Events::Services;

void EventService::initialize()
{
    setContext(this);

    glfwSetKeyCallback(glfwGetCurrentContext(), &EventService::_keyCallback);
}

void EventService::registerHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler)
{
    _handlers[key].push_back(handler);
}

void EventService::_keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    auto that = getContext();

    if (that->_handlers.find(static_cast<Models::KeyboardKeys>(key)) != that->_handlers.end())
    {
        for (auto &handler : that->_handlers[static_cast<Models::KeyboardKeys>(key)])
        {
            handler(action == GLFW_PRESS);
        }
    }
}