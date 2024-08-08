#ifndef TENGINE_ENGINEPARAMETERS_H
#define TENGINE_ENGINEPARAMETERS_H

#include "IEngineParameters.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Models
{
    class EngineParameters : public IEngineParameters
    {
    public:
        EngineParameters();

        std::shared_ptr<IGraphicsParameters> getGraphicsParameters();

        void setGraphicsParameters(std::shared_ptr<IGraphicsParameters> graphicsParameters);

    private:
        std::shared_ptr<IGraphicsParameters> _graphicsParameters;
    };
}

#endif //TENGINE_ENGINEPARAMETERS_H