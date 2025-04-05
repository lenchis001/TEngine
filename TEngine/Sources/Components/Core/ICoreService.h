#ifndef TEENGINE_ICORESERVICE_H
#define TEENGINE_ICORESERVICE_H

#include <functional>

#include "Models/ThreadType.h"

namespace TEngine::Components::Core
{
    class ICoreService
    {
    public:
        virtual void addToQueue(Core::Models::ThreadType threadType, std::function<void()> action, bool wait = false) = 0;

        virtual void processQueue(Core::Models::ThreadType threadType) = 0;
    };
}

#endif // TEENGINE_ICORESERVICE_H