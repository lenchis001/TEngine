#ifndef TENGINE_THREADTYPE_H
#define TENGINE_THREADTYPE_H

namespace TEngine::Components::Core::Models
{
    enum ThreadType : int
    {
        POOL_PROCESSING = 0,
        RENDERING = 1,
        GUI = 2,
    };
}

#endif // TENGINE_THREADTYPE_H