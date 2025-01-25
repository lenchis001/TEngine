#ifndef TENGINE_IRENDERINGSEQUENCESERVICE_H
#define TENGINE_IRENDERINGSEQUENCESERVICE_H

#include <vector>
#include <memory>

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"

namespace TEngine::Components::Graphics::Rendering::Scene::Sequence
{
    class IRenderingSequenceService
    {
    public:
        virtual ~IRenderingSequenceService() = default;

        virtual std::vector<std::shared_ptr<RenderingStrategies::IRenderingStrategy>> generateSequence(
            std::shared_ptr<RenderingStrategies::IRenderingStrategy> root,
            const Graphics::Models::Vector3df &cameraPosition) = 0;
    };
}

#endif // TENGINE_IRENDERINGSEQUENCESERVICE_H