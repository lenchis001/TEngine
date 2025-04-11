#include "Engine.h"

#ifdef __ANDROID__
#include <EGL/egl.h>
#else
#include <GL/gl.h>
#endif

using namespace TEngine;

Engine::Engine(
    std::shared_ptr<IGraphicsService> graphicsService,
    std::shared_ptr<IEventService> eventService,
    std::shared_ptr<IAudioService> audioService,
    std::shared_ptr<ISerializationService> serializationService,
    std::shared_ptr<IDeserializationService> deserializationService,
    std::shared_ptr<INetworkService> networkService,
    std::shared_ptr<IWebSocketFactory> webSocketFactory,
    std::shared_ptr<ICoreService> coreService)
    : _graphicsService(graphicsService),
      _eventService(eventService),
      _audioService(audioService),
      _serializationService(serializationService),
      _deserializationService(deserializationService),
      _networkService(networkService),
      _webSocketFactory(webSocketFactory),
      _coreService(coreService)
{
}

Engine::~Engine()
{
}

void Engine::initialize(std::shared_ptr<IEngineParameters> parameters)
{
    _graphicsService->initialize(parameters->getGraphicsParameters());

    _eventService->initialize();

    _audioService->initialize();
}

void Engine::deinitialize()
{
    _graphicsService->deinitialize();
}

std::shared_ptr<IGraphicsService> Engine::getGraphicsService()
{
    return _graphicsService;
}

std::shared_ptr<IEventService> Engine::getEventService()
{
    return _eventService;
}

std::shared_ptr<IAudioService> Engine::getAudioService()
{
    return _audioService;
}

std::shared_ptr<ISerializationService> Engine::getSerializationService()
{
    return _serializationService;
}

std::shared_ptr<IDeserializationService> Engine::getDeserializationService()
{
    return _deserializationService;
}

std::shared_ptr<INetworkService> Engine::getNetworkService()
{
    return _networkService;
}

std::shared_ptr<IWebSocketFactory> Engine::getWebSocketFactory()
{
    return _webSocketFactory;
}

std::shared_ptr<ICoreService> Engine::getCoreService()
{
    return _coreService;
}