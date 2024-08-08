#ifndef TENGINE_ENGINEPARAMETERS_H
#define TENGINE_ENGINEPARAMETERS_H

#include "Components/Graphics/Models/GraphicsParameters.h"

using GraphicsParameters = TEngine::Components::Graphics::Models::GraphicsParameters;

namespace TEngine::Models
{
    class EngineParameters
    {
    public:
        EngineParameters();

        GraphicsParameters &getGraphicsParameters();

        void setGraphicsParameters(const GraphicsParameters &graphicsParameters);

    private:
        GraphicsParameters _graphicsParameters;
    };
}

#endif //TENGINE_ENGINEPARAMETERS_H