#ifndef TENGINE_MOUSE_BUTTONS_H
#define TENGINE_MOUSE_BUTTONS_H

namespace TEngine::Components::Events::Models
{
    enum class MouseButtons : int
    {
        BUTTON_1 = 0,
        BUTTON_2 = 1,
        BUTTON_3 = 2,
        BUTTON_4 = 3,
        BUTTON_5 = 4,
        BUTTON_6 = 5,
        BUTTON_7 = 6,
        BUTTON_8 = 7,
        BUTTON_UNKNOWN = -1,
        BUTTON_LEFT = BUTTON_1,
        BUTTON_RIGHT = BUTTON_2,
        BUTTON_MIDDLE = BUTTON_3
    };
}

#endif // TENGINE_MOUSE_BUTTONS_H