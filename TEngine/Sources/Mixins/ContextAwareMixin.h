#ifndef TENGINE_MIXINS_CONTEXT_AWARE_MIXIN_H
#define TENGINE_MIXINS_CONTEXT_AWARE_MIXIN_H

#include "cassert"

namespace TEngine::Mixins
{
    template <typename T>
    class ContextAwareMixin
    {
    protected:
        static T *getContext() { return _context; }

        static void setContext(T *context)
        {
            assert(_context == nullptr && "Context was already set");

            _context = context;
        }

    private:
        static thread_local T *_context;
    };

    template <typename T>
    thread_local T *ContextAwareMixin<T>::_context = nullptr;
}

#endif // TENGINE_MIXINS_CONTEXT_AWARE_MIXIN_H