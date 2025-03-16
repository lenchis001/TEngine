#ifndef TENGINE_THREADSAFEEXECUTIONAWARE_H
#define TENGINE_THREADSAFEEXECUTIONAWARE_H

#include <functional>
#include <queue>
#include <atomic>

#include "SpinLock.h"

namespace TEngine::Mixins
{
    class ThreadSafeExecutionAware
    {
    public:
        ThreadSafeExecutionAware() : stop(false)
        {
        }

        ~ThreadSafeExecutionAware()
        {
            std::lock_guard<SpinLock> lock(queueLock);
            stop = true;
        }

        void addTask(const std::function<void()> &task)
        {
            std::lock_guard<SpinLock> lock(queueLock);
            taskQueue.push(task);
        }

        void execute()
        {
            while (true)
            {
                std::function<void()> task;
                {
                    std::lock_guard<SpinLock> lock(queueLock);
                    if (stop && taskQueue.empty())
                    {
                        return;
                    }
                    if (!taskQueue.empty())
                    {
                        task = taskQueue.front();
                        taskQueue.pop();
                    }
                }
                if (task)
                {
                    task();
                }
            }
        }

    private:
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

        std::queue<std::function<void()>> taskQueue;
        SpinLock queueLock;
        std::atomic<bool> stop;
    };
}

#endif // TENGINE_THREADSAFEEXECUTIONAWARE_H