#ifndef IENGINE_H
#define IENGINE_H

#include "memory"

#include "Components/Graphics/IGraphicsService.h"

#include "Models/EngineParameters.h"

using IGraphicsService = TEngine::Components::Graphics::Services::IGraphicsService;
using EngineParameters = TEngine::Models::EngineParameters;

namespace TEngine
{
    class IEngine
    {
    public:
        virtual std::shared_ptr<IGraphicsService> getGraphicsService() = 0;

        virtual void initialize(EngineParameters& parameters) = 0;

        virtual ~IEngine() = default;
    };

    std::shared_ptr<IEngine> createEngine();
}

#endif // IENGINE_H