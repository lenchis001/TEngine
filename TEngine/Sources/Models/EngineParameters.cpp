#include "EngineParameters.h"

#include "Components/Graphics/Models/GraphicsParameters.h"

using namespace TEngine::Models;
using namespace TEngine::Components::Graphics::Models;

EngineParameters::EngineParameters()
{
    setGraphicsParameters(std::make_shared<GraphicsParameters>());
}

std::shared_ptr<IGraphicsParameters> EngineParameters::getGraphicsParameters()
{
    return _graphicsParameters;
}

void EngineParameters::setGraphicsParameters(std::shared_ptr<IGraphicsParameters> graphicsParameters)
{
    _graphicsParameters = graphicsParameters;
}