#include "FunctionConveyer.h"

#include <cassert>

using namespace Alice::Core::Thread;

FunctionConveyer::~FunctionConveyer()
{
    assert(_functions.empty() && "FunctionConveyer is not empty");
}

void FunctionConveyer::addFunction(std::function<void()> function)
{
    std::lock_guard<std::mutex> lock(_mtx);

    _functions.push(function);
}

void FunctionConveyer::executeFunctions()
{
    std::lock_guard<std::mutex> lock(_mtx);

    while (!_functions.empty())
    {
        auto function = _functions.front();
        function();
        _functions.pop();
    }
}