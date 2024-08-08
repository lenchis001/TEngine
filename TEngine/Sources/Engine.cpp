#include "Engine.h"

using namespace TEngine;

Engine::Engine(std::shared_ptr<IGraphicsService> graphicsService)
    : _graphicsService(graphicsService)
{
}

Engine::~Engine()
{
}

void Engine::initialize(std::shared_ptr<IEngineParameters> parameters)
{
	_graphicsService->initialize(parameters->getGraphicsParameters());
}

std::shared_ptr<IGraphicsService> Engine::getGraphicsService()
{
    return _graphicsService;
}