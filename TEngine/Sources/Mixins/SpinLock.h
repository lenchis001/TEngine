#ifndef TENGINE_SPINLOCK_H
#define TENGINE_SPINLOCK_H

#include <thread>
#include <atomic>

namespace TEngine::Mixins
{
    class SpinLock
    {
    public:
        void lock()
        {
            while (flag.test_and_set(std::memory_order_acquire))
            {
                // busy-wait
            }
        }

        void unlock()
        {
            flag.clear(std::memory_order_release);
        }

    private:
        std::atomic_flag flag = ATOMIC_FLAG_INIT;
    };
}

#endif // TENGINE_SPINLOCK_H