#include "EngineParameters.h"

using namespace TEngine::Models;

EngineParameters::EngineParameters()
{
    setGraphicsParameters(GraphicsParameters());
}

GraphicsParameters &EngineParameters::getGraphicsParameters()
{
    return _graphicsParameters;
}

void EngineParameters::setGraphicsParameters(const GraphicsParameters &graphicsParameters)
{
    _graphicsParameters = graphicsParameters;
}