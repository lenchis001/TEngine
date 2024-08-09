#ifndef TENGINE_IRENDERINGSERVICE_H
#define TENGINE_IRENDERINGSERVICE_H

#include "memory"

#include "Components/Graphics/Rendering/Models/IRenderingParameters.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IRenderableObject.h"
#include "Components/Graphics/Models/PrimitiveTypes.h"

namespace TEngine::Components::Graphics::Rendering::Services
{
    class IRenderingService
    {
    public:
        virtual void render() = 0;

        virtual void initialize(std::shared_ptr<TEngine::Components::Graphics::Rendering::Models::IRenderingParameters> parameters) = 0;

        virtual void addToRendering(std::shared_ptr<
            Components::Graphics::Rendering::Models::RenderableObjects::IRenderableObject> object,
            Components::Graphics::MeshLoading::Models::PrimitiveTypes type
            ) = 0;

        virtual ~IRenderingService() = default;
    };
}

#endif //TENGINE_IRENDERINGSERVICE_H