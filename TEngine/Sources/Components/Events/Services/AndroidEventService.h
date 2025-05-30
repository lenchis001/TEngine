#ifdef __ANDROID__

#ifndef TENGINE_ANDROID_EVENT_SERVICE_H
#define TENGINE_ANDROID_EVENT_SERVICE_H

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <game-activity/GameActivity.h>
#include <android/native_activity.h>

#include "EventServiceBase.h"

#include "Mixins/ContextAwareMixin.h"

using namespace TEngine::Mixins;

namespace TEngine::Components::Events::Services
{
    class AndroidEventService : public EventServiceBase, public ContextAwareMixin<AndroidEventService>
    {
    public:
        AndroidEventService(android_app *app);
        ~AndroidEventService() override;

        void initialize() override;

        void setCursorePosition(const Vector2di &value) override;
        void setCursorVisibility(bool isVisible) override;

    private:
        static bool _onKeyDown(GameActivity* activity, const GameActivityKeyEvent* event);
        static bool _onTouch(GameActivity* activity, const GameActivityMotionEvent* event);

        android_app *_app;
    };
}

#endif // TENGINE_ANDROID_EVENT_SERVICE_H

#endif // __ANDROID__
