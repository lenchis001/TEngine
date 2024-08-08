#ifndef TENGINE_GRAPHICSPARAMETERS_H
#define TENGINE_GRAPHICSPARAMETERS_H

#include "IGraphicsParameters.h"

using namespace TEngine::Components::Graphics::Models::Rendering;

namespace TEngine::Components::Graphics::Models
{
    class GraphicsParameters : public IGraphicsParameters
    {
    public:
        GraphicsParameters();

        std::shared_ptr<IRenderingParameters> getRenderingParameters();

        void setRenderingParameters(const std::shared_ptr<IRenderingParameters> renderingParameters);

    private:
        std::shared_ptr<IRenderingParameters> _renderingParameters;
    };
}

#endif // TENGINE_GRAPHICSPARAMETERS_H