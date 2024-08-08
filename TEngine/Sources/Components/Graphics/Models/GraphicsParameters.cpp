#include "GraphicsParameters.h"

#include "Rendering/RenderingParameters.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Models::Rendering;

GraphicsParameters::GraphicsParameters()
{
    setRenderingParameters(std::make_shared<RenderingParameters>());
}

std::shared_ptr<IRenderingParameters> GraphicsParameters::getRenderingParameters()
{
    return _renderingParameters;
}

void GraphicsParameters::setRenderingParameters(std::shared_ptr<IRenderingParameters> renderingParameters)
{
    _renderingParameters = renderingParameters;
}