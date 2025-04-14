#include "ICoreService.h"

#include <vector>

#include "Mixins/SpinLock.h"

using namespace TEngine::Mixins;
using namespace TEngine::Components::Core::Models;

namespace TEngine::Components::Core
{
    class CoreService : public ICoreService
    {
    public:
        void addToQueue(ThreadType threadType, std::function<void()> action, bool wait = false) override;

        void processQueue(ThreadType threadType) override;

    private:
        void _addToQueueNoWait(ThreadType threadType, std::function<void()> &&action);
        void _addToQueueAndWait(ThreadType threadType, std::function<void()> &&action);

        std::vector<std::function<void()>> _poolProcessingQueue;
        std::vector<std::function<void()>> _renderingQueue;
        std::vector<std::function<void()>> _guiQueue;

        SpinLock _renderingQueueLock;
        SpinLock _guiQueueLock;
    };
}