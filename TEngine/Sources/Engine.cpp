#include "Engine.h"

#include "GLFW/glfw3.h"

using namespace TEngine;

Engine::Engine(
    std::shared_ptr<IGraphicsService> graphicsService,
    std::shared_ptr<IEventService> eventService)
    : _graphicsService(graphicsService),
      _eventService(eventService)
{
}

Engine::~Engine()
{
}

void Engine::initialize(std::shared_ptr<IEngineParameters> parameters)
{
    _graphicsService->initialize(parameters->getGraphicsParameters());

    _eventService->initialize();
}

std::shared_ptr<IGraphicsService> Engine::getGraphicsService()
{
    return _graphicsService;
}

std::shared_ptr<IEventService> Engine::getEventService()
{
    return _eventService;
}