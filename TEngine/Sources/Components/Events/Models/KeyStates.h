#ifndef TENGINE_KEY_STATES_H
#define TENGINE_KEY_STATES_H

namespace TEngine::Components::Events::Models
{
    enum class KeyStates : int
    {
        RELEASE = 0,
        PRESS = 1,
        REPEAT = 2
    };
}

#endif // TENGINE_KEY_STATES_H