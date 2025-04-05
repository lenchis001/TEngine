#include "CoreService.h"

#include <condition_variable>
#ifdef TENGINE_DEBUG
#include <iostream>
#endif // TENGINE_DEBUG


using namespace TEngine::Components::Core;

void CoreService::addToQueue(ThreadType threadType, std::function<void()> action, bool wait)
{
    if (wait)
    {
        _addToQueueAndWait(threadType, std::move(action));
    }
    else
    {
        _addToQueueNoWait(threadType, std::move(action));
    }
}

void CoreService::processQueue(ThreadType threadType)
{
    #ifdef TENGINE_DEBUG
    try{
    #endif // TENGINE_DEBUG

    switch (threadType)
    {
    case ThreadType::RENDERING:
    {
        _renderingQueueLock.lock();
        for (auto &action : _renderingQueue)
        {
            action();
        }
        _renderingQueue.clear();
        _renderingQueueLock.unlock();
        break;
    }
    default:
        break;
    }

    #ifdef TENGINE_DEBUG
    } catch (std::exception &e) {
        std::cerr << "Exception in CoreService::processQueue: " << e.what() << std::endl;
    } catch (...) {
        std::cerr << "Unknown exception in CoreService::processQueue" << std::endl;
    }
    #endif // TENGINE_DEBUG
}

void CoreService::_addToQueueNoWait(ThreadType threadType, std::function<void()> &&action)
{
    switch (threadType)
    {
    case ThreadType::POOL_PROCESSING:
        _poolProcessingQueue.push_back(std::move(action));
        break;
    case ThreadType::RENDERING:
        _renderingQueueLock.lock();
        _renderingQueue.push_back(std::move(action));
        _renderingQueueLock.unlock();
        break;
    case ThreadType::GUI:
        _guiQueue.push_back(std::move(action));
        break;
    default:
        break;
    }
}

void CoreService::_addToQueueAndWait(ThreadType threadType, std::function<void()> &&action)
{
    SpinLock locker;

    locker.lock();

    _addToQueueNoWait(
        threadType, 
        [&action, &locker]()
        {
            action();
            locker.unlock(); 
        });

    locker.lock();
}