#ifdef __ANDROID__

#include "AndroidEventService.h"

namespace TEngine::Components::Events::Services
{
    AndroidEventService::AndroidEventService(android_app *app)
        : EventServiceBase(),
          _app(app)
    {
        setContext(this);
    }

    AndroidEventService::~AndroidEventService()
    {
        setContext(nullptr);
    }

    void AndroidEventService::initialize()
    {
        // Initialization logic for Android-specific event handling
    }

    void AndroidEventService::setCursorePosition(const Vector2di &value)
    {
        // Set cursor position logic for Android
    }

    void AndroidEventService::setCursorVisibility(bool isVisible)
    {
        // Set cursor visibility logic for Android
    }

    void AndroidEventService::handleInput(AInputEvent *event)
    {
        if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_KEY)
        {
            KeyboardKeys key = static_cast<KeyboardKeys>(AKeyEvent_getKeyCode(event));
            KeyStates action = (AKeyEvent_getAction(event) == AKEY_EVENT_ACTION_DOWN) ? KeyStates::Pressed : KeyStates::Released;
            fireKeyHandler(key, 0, action, 0);
        }
        else if (AInputEvent_getType(event) == AINPUT_EVENT_TYPE_MOTION)
        {
            int32_t action = AMotionEvent_getAction(event) & AMOTION_EVENT_ACTION_MASK;
            if (action == AMOTION_EVENT_ACTION_MOVE)
            {
                int x = static_cast<int>(AMotionEvent_getX(event, 0));
                int y = static_cast<int>(AMotionEvent_getY(event, 0));
                fireCursorMoveHandler(x, y);
            }
            else if (action == AMOTION_EVENT_ACTION_DOWN || action == AMOTION_EVENT_ACTION_UP)
            {
                MouseButtons button = MouseButtons::Left; // Assuming left button for simplicity
                KeyStates state = (action == AMOTION_EVENT_ACTION_DOWN) ? KeyStates::Pressed : KeyStates::Released;
                fireMouseButtonHandler(button, state, 0);
            }
        }
    }
}

#endif // __ANDROID__