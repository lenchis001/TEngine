#include "EventServiceBase.h"

#include <cassert>

using namespace TEngine::Components::Events::Services;

EventServiceBase::~EventServiceBase()
{
    assert(_keyboardHandlers.empty() && "Not all keyboard handlers were unregistered");
    assert(_cursorMoveHandlers.empty() && "Not all mouse handlers were unregistered");
    assert(_mouseButtonHandlers.empty() && "Not all mouse button handlers were unregistered");
    assert(_scrollHandlers.empty() && "Not all scroll handlers were unregistered");
    assert(_charHandlers.empty() && "Not all char handlers were unregistered");
}

void EventServiceBase::registerKeyHandler(const KeyboardEventHandler &handler)
{
    _keyboardHandlers.push_back(handler);
}

void EventServiceBase::unregisterKeyHandler(const KeyboardEventHandler &handler)
{
    removeEventHandler(_keyboardHandlers, handler);
}

void EventServiceBase::fireKeyHandler(KeyboardKeys key, int scancode, KeyStates action, int mods)
{
    for (auto &handler : this->_keyboardHandlers)
    {
        if (handler(key, scancode, action, mods))
        {
            break;
        }
    }
}

void EventServiceBase::registerCursorMoveHandler(const CursorMoveEventHandler &handler)
{
    _cursorMoveHandlers.push_back(handler);
}

void EventServiceBase::unregisterCursorMoveHandler(const CursorMoveEventHandler &handler)
{
    removeEventHandler(_cursorMoveHandlers, handler);
}

void EventServiceBase::fireCursorMoveHandler(int xpos, int ypos)
{
    for (auto &handler : this->_cursorMoveHandlers)
    {
        if (handler(xpos, ypos))
        {
            break;
        }
    }
}

void EventServiceBase::registerMouseButtonHandler(const MouseButtonEventHandler &handler)
{
    _mouseButtonHandlers.push_back(handler);
}

void EventServiceBase::unregisterMouseButtonHandler(const MouseButtonEventHandler &handler)
{
    removeEventHandler(_mouseButtonHandlers, handler);
}

void EventServiceBase::fireMouseButtonHandler(MouseButtons button, KeyStates action, int mods)
{
    for (auto &handler : this->_mouseButtonHandlers)
    {
        if (handler(button, action, mods))
        {
            break;
        }
    }
}

void EventServiceBase::registerScrollHandler(const ScrollEventHandler &handler)
{
    _scrollHandlers.push_back(handler);
}

void EventServiceBase::unregisterScrollHandler(const ScrollEventHandler &handler)
{
    removeEventHandler(_scrollHandlers, handler);
}

void EventServiceBase::fireScrollHandler(float xoffset, float yoffset)
{
    for (auto &handler : this->_scrollHandlers)
    {
        if (handler(xoffset, yoffset))
        {
            break;
        }
    }
}

void EventServiceBase::registerCharHandler(const CharEventHandler &handler)
{
    _charHandlers.push_back(handler);
}

void EventServiceBase::unregisterCharHandler(const CharEventHandler &handler)
{
    removeEventHandler(_charHandlers, handler);
}

void EventServiceBase::fireCharHandler(unsigned int codepoint)
{
    for (auto &handler : this->_charHandlers)
    {
        if (handler(codepoint))
        {
            break;
        }
    }
}

void EventServiceBase::registerCursorEnterHandler(const CursorEnterEventHandler &handler)
{
    _cursorEnterHandlers.push_back(handler);
}

void EventServiceBase::unregisterCursorEnterHandler(const CursorEnterEventHandler &handler)
{
    removeEventHandler(_cursorEnterHandlers, handler);
}

void EventServiceBase::fireCursorEnterHandler(bool entered)
{
    for (auto &handler : this->_cursorEnterHandlers)
    {
        if (handler(entered))
        {
            break;
        }
    }
}