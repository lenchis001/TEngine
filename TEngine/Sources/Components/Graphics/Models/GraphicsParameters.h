#ifndef TENGINE_GRAPHICSPARAMETERS_H
#define TENGINE_GRAPHICSPARAMETERS_H

#include "Rendering/RenderingParameters.h"

using RenderingParameters = TEngine::Components::Graphics::Models::Rendering::RenderingParameters;

namespace TEngine::Components::Graphics::Models
{
    class GraphicsParameters
    {
    public:
        GraphicsParameters();

        RenderingParameters &getRenderingParameters();

        void setRenderingParameters(const RenderingParameters &renderingParameters);

    private:
        RenderingParameters _renderingParameters;
    };
}

#endif // TENGINE_GRAPHICSPARAMETERS_H