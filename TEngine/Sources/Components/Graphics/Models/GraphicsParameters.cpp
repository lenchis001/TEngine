#include "GraphicsParameters.h"

using namespace TEngine::Components::Graphics::Models;

GraphicsParameters::GraphicsParameters()
{
    setRenderingParameters(RenderingParameters());
}

RenderingParameters& GraphicsParameters::getRenderingParameters()
{
    return _renderingParameters;
}

void GraphicsParameters::setRenderingParameters(const RenderingParameters &renderingParameters)
{
    _renderingParameters = renderingParameters;
}