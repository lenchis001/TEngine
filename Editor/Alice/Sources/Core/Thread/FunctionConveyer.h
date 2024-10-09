#ifndef ALICE_FUNCTION_CONVEYER_H
#define ALICE_FUNCTION_CONVEYER_H

#include <queue>
#include <functional>
#include <mutex>

namespace Alice::Core::Thread
{
    class FunctionConveyer
    {
    public:
        ~FunctionConveyer();

        void addFunction(std::function<void()> function);
        void executeFunctions();

    private:
        std::queue<std::function<void()>> _functions;
        std::mutex _mtx;
    };
}

#endif // !ALICE_FUNCTION_CONVEYER_H