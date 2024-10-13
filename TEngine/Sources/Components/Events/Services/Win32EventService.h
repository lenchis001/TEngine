#ifdef _WIN32

#ifndef TENGINE_WIN32_EVENT_SERVICE_H
#define TENGINE_WIN32_EVENT_SERVICE_H

#include "EventServiceBase.h"

namespace TEngine::Components::Events::Services
{
    class Win32EventService : public EventServiceBase
    {
    public:
        void initialize() override;

        void setCursorePosition(const Vector2di &value) override;
        void setCursorVisibility(bool isVisible) override;
    };
}

#endif // TENGINE_WIN32_EVENT_SERVICE_H

#endif // _WIN32