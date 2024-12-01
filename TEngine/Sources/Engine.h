#ifndef Engine_H
#define Engine_H

#include "IEngine.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics;
using namespace TEngine::Components::Events::Services;
using namespace TEngine::Components::Audio::Services;
using namespace TEngine::Components::State::Serialization;
using namespace TEngine::Components::State::Deserialization;
using namespace TEngine::Components::Network::Http;

namespace TEngine
{
    class Engine : public IEngine
    {
    public:
        Engine(
            std::shared_ptr<IGraphicsService> graphicsService,
            std::shared_ptr<IEventService> eventService,
            std::shared_ptr<IAudioService> audioService,
            std::shared_ptr<ISerializationService> serializationService,
            std::shared_ptr<IDeserializationService> deserializationService,
            std::shared_ptr<INetworkService> networkService);
        ~Engine();

        void initialize(std::shared_ptr<IEngineParameters> parameters) override;

        void deinitialize() override;

        std::shared_ptr<IGraphicsService> getGraphicsService() override;

        std::shared_ptr<IEventService> getEventService() override;

        std::shared_ptr<IAudioService> getAudioService() override;

        std::shared_ptr<ISerializationService> getSerializationService() override;
        
        std::shared_ptr<IDeserializationService> getDeserializationService() override;

        std::shared_ptr<INetworkService> getNetworkService() override;
    private:
        std::shared_ptr<IGraphicsService> _graphicsService;
        std::shared_ptr<IEventService> _eventService;
        std::shared_ptr<IAudioService> _audioService;
        std::shared_ptr<ISerializationService> _serializationService;
        std::shared_ptr<IDeserializationService> _deserializationService;
        std::shared_ptr<INetworkService> _networkService;
    };
}

#endif // Engine_H