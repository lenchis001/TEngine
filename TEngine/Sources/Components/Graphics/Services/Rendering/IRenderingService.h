#ifndef TENGINE_IRENDERINGSERVICE_H
#define TENGINE_IRENDERINGSERVICE_H

#include "Components/Graphics/Models/Rendering/RenderingParameters.h"

using RenderingParameters = TEngine::Components::Graphics::Models::Rendering::RenderingParameters;

namespace TEngine::Components::Graphics::Services::Rendering
{
    class IRenderingService
    {
    public:
        virtual void render() = 0;

        virtual void initialize(RenderingParameters& parameters) = 0;

        virtual ~IRenderingService() = default;
    };
}

#endif //TENGINE_IRENDERINGSERVICE_H