#ifndef TENGINE_EVENT_SERVICE_BASE_H
#define TENGINE_EVENT_SERVICE_BASE_H

#include "IEventService.h"

#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cassert>

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Events::Models;

namespace TEngine::Components::Events::Services
{
    class EventServiceBase : public IEventService
    {
    public:
        ~EventServiceBase() override;

        void registerKeyHandler(const KeyboardEventHandler &handler) override;
        void unregisterKeyHandler(const KeyboardEventHandler &handler) override;
        void fireKeyHandler(int key, int scancode, int action, int mods) override;

        void registerCursorMoveHandler(const CursorMoveEventHandler &handler) override;
        void unregisterCursorMoveHandler(const CursorMoveEventHandler &handler) override;
        void fireCursorMoveHandler(float xpos, float ypos) override;

        void registerMouseButtonHandler(const MouseButtonEventHandler &handler) override;
        void unregisterMouseButtonHandler(const MouseButtonEventHandler &handler) override;
        void fireMouseButtonHandler(int button, int action, int mods) override;

        void registerScrollHandler(const ScrollEventHandler &handler) override;
        void unregisterScrollHandler(const ScrollEventHandler &handler) override;
        void fireScrollHandler(float xoffset, float yoffset) override;

        void registerCharHandler(const CharEventHandler &handler) override;
        void unregisterCharHandler(const CharEventHandler &handler) override;
        void fireCharHandler(unsigned int codepoint) override;

        void registerCursorEnterHandler(const CursorEnterEventHandler &handler) override;
        void unregisterCursorEnterHandler(const CursorEnterEventHandler &handler) override;
        void fireCursorEnterHandler(bool entered) override;

    protected:
        std::vector<KeyboardEventHandler> _keyboardHandlers;
        std::vector<CursorMoveEventHandler> _cursorMoveHandlers;
        std::vector<MouseButtonEventHandler> _mouseButtonHandlers;
        std::vector<ScrollEventHandler> _scrollHandlers;
        std::vector<CharEventHandler> _charHandlers;
        std::vector<CursorEnterEventHandler> _cursorEnterHandlers;

    private:
        template <class T>
        static void removeEventHandler(std::vector<T> &handlers, const T &handler)
        {
            auto handlersSize = handlers.size();

            handlers.erase(std::remove_if(handlers.begin(), handlers.end(), [&handler](const T &h)
                                          { return h.target_type() == handler.target_type() && h.template target<T>() == handler.template target<T>(); }),
                           handlers.end());

            assert((handlersSize - 1) == handlers.size() && "Handler was not found");
        }
    };
}

#endif // TENGINE_EVENT_SERVICE_BASE_H