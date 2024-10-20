#ifndef Engine_H
#define Engine_H

#include "IEngine.h"

#include "GLFW/glfw3.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics;
using namespace TEngine::Components::Events::Services;
using namespace TEngine::Components::Audio::Services;
using namespace TEngine::Components::State::Serialization;

namespace TEngine
{
    class Engine : public IEngine
    {
    public:
        Engine(
            std::shared_ptr<IGraphicsService> graphicsService,
            std::shared_ptr<IEventService> eventService,
            std::shared_ptr<IAudioService> audioService,
            std::shared_ptr<ISerializationService> serializationService);
        ~Engine();

        void initialize(std::shared_ptr<IEngineParameters> parameters) override;

        void deinitialize() override;

        std::shared_ptr<IGraphicsService> getGraphicsService() override;

        std::shared_ptr<IEventService> getEventService() override;

        std::shared_ptr<IAudioService> getAudioService() override;

        std::shared_ptr<ISerializationService> getSerializationService() override;

    private:
        std::shared_ptr<IGraphicsService> _graphicsService;
        std::shared_ptr<IEventService> _eventService;
        std::shared_ptr<IAudioService> _audioService;
        std::shared_ptr<ISerializationService> _serializationService;
    };
}

#endif // Engine_H