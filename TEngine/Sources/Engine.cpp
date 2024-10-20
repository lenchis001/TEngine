#include "Engine.h"

#include "GLFW/glfw3.h"

using namespace TEngine;

Engine::Engine(
    std::shared_ptr<IGraphicsService> graphicsService,
    std::shared_ptr<IEventService> eventService,
    std::shared_ptr<IAudioService> audioService,
    std::shared_ptr<ISerializationService> serializationService)
    : _graphicsService(graphicsService),
      _eventService(eventService),
      _audioService(audioService),
      _serializationService(serializationService)
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