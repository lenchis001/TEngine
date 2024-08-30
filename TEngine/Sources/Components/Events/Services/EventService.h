#ifndef TENGINE_EVENT_SERVICE_H
#define TENGINE_EVENT_SERVICE_H

#include "IEventService.h"

#include "unordered_map"
#include "vector"

#include "GLFW/glfw3.h"

#include "Mixins/ContextAwareMixin.h"

using namespace TEngine::Components::Events::Models;
using namespace TEngine::Mixins;

namespace TEngine::Components::Events::Services
{
    class EventService : public IEventService, public ContextAwareMixin<EventService>
    {
    public:
        EventService() = default;
        ~EventService() override = default;

        void initialize() override;

        void registerHandler(Models::KeyboardKeys key, const KeyboardEventHandler &handler) override;

    private:
        static void _keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

        std::unordered_map<KeyboardKeys, std::vector<KeyboardEventHandler>> _handlers;
    };
}

#endif // TENGINE_EVENT_SERVICE_H