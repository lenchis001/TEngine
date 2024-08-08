#ifndef TENGINE_IRENDERINGSERVICE_H
#define TENGINE_IRENDERINGSERVICE_H

#include "memory"

#include "Components/Graphics/Models/Rendering/IRenderingParameters.h"

namespace TEngine::Components::Graphics::Services::Rendering
{
    class IRenderingService
    {
    public:
        virtual void render() = 0;

        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Models::Rendering::IRenderingParameters> parameters) = 0;

        virtual ~IRenderingService() = default;
    };
}

#endif //TENGINE_IRENDERINGSERVICE_H