#ifdef _WIN32

#include "Win32EventService.h"

#include <windows.h>

using namespace TEngine::Components::Events::Services;

void Win32EventService::initialize()
{
}

void Win32EventService::setCursorePosition(const Vector2di &value)
{
    SetCursorPos(value.getX(), value.getY());
}

void Win32EventService::setCursorVisibility(bool isVisible)
{
    ShowCursor(isVisible);
}

#endif // _WIN32