#ifdef __ANDROID__

#include <android/log.h>

#include "AndroidEventService.h"

using namespace TEngine::Components::Events::Models;

namespace TEngine::Components::Events::Services
{
    AndroidEventService::AndroidEventService(android_app *app)
        : EventServiceBase(),
          _app(app)
    {
    }

    AndroidEventService::~AndroidEventService()
    {
        setContext(nullptr);
    }

    AndroidEventService *global;
    void AndroidEventService::initialize()
    {
        AndroidEventService::setContext(this);
        global = this;

        GameActivity *activity = (GameActivity *)_app->activity;

        activity->callbacks->onKeyDown = &AndroidEventService::_onKeyDown;
        activity->callbacks->onTouchEvent = &AndroidEventService::_onTouch;
    }

    void AndroidEventService::setCursorePosition(const Vector2di &value)
    {
        // Set cursor position logic for Android
    }

    void AndroidEventService::setCursorVisibility(bool isVisible)
    {
        // Set cursor visibility logic for Android
    }

    bool AndroidEventService::_onKeyDown(GameActivity *activity, const GameActivityKeyEvent *event)
    {
        return true;
    }

    bool AndroidEventService::_onTouch(GameActivity *activity, const GameActivityMotionEvent *event)
    {
        int action = event->action;
        int pointerCount = event->pointerCount;
        auto that = AndroidEventService::getContext();

        for (int i = 0; i < pointerCount; ++i)
        {
            auto axes = event->pointers[i];

            global->fireCursorMoveHandler(static_cast<int>(axes.rawX), static_cast<int>(axes.rawY));
        }

        if (action == AMOTION_EVENT_ACTION_DOWN || action == AMOTION_EVENT_ACTION_UP)
        {
            MouseButtons button = static_cast<MouseButtons>(event->buttonState);
            KeyStates state = static_cast<KeyStates>(action);
            global->fireMouseButtonHandler(button, state, 0);

            if (action == AMOTION_EVENT_ACTION_UP) {
                global->fireCursorMoveHandler(static_cast<int>(-1), static_cast<int>(-1));
            }
        }

        return true;
    }
}

#endif // __ANDROID__