#ifndef TENGINE_IBIG_WORLD_SERVICE_H
#define TENGINE_IBIG_WORLD_SERVICE_H

#include "vector"
#include "memory"

#include "Components/Graphics/Models/Matrix4x4.h"
#include "Components/Graphics/Rendering/Models/Optimization/IBigWorldParameters.h"

#include "Components/Graphics/Rendering/Services/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Services::Optimization
{
    class IBigWorldService
    {
    public:
        virtual ~IBigWorldService() = default;

        virtual void initialize(std::shared_ptr<Components::Graphics::Rendering::Models::Optimization::IBigWorldParameters> parameters) = 0;

        virtual void render(
            const std::vector<std::shared_ptr<Components::Graphics::Rendering::Services::RenderingStrategies::IRenderingStrategy>> strategies,
            const Components::Graphics::Models::Matrix4x4f &vpMatrix) = 0;
    };
}

#endif // TENGINE_IBIG_WORLD_SERVICE_H