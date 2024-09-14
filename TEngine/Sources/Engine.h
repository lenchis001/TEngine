#ifndef Engine_H
#define Engine_H

#include "IEngine.h"

#include "GLFW/glfw3.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Services;
using namespace TEngine::Components::Events::Services;
using namespace TEngine::Components::Audio::Services;

namespace TEngine
{
    class Engine : public IEngine
    {
    public:
        Engine(
            std::shared_ptr<IGraphicsService> graphicsService,
            std::shared_ptr<IEventService> eventService,
            std::shared_ptr<IAudioService> audioService);
        ~Engine();

        void initialize(std::shared_ptr<IEngineParameters> parameters) override;

        std::shared_ptr<IGraphicsService> getGraphicsService() override;

        std::shared_ptr<IEventService> getEventService() override;

        std::shared_ptr<IAudioService> getAudioService() override;

    private:
        std::shared_ptr<IGraphicsService> _graphicsService;
        std::shared_ptr<IEventService> _eventService;
        std::shared_ptr<IAudioService> _audioService;
    };
}

#endif // Engine_H