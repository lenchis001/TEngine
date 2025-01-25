#ifndef TENGINE_EMPTYRENDERINGSTRATEGY_H
#define TENGINE_EMPTYRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Empty
{
    class EmptyRenderingStrategy : public RenderingStrategyBase
    {
    public:
        EmptyRenderingStrategy(OnDeleteCallback onDeleteCallback);

        std::type_index getType() const override;

        Rendering::Models::Priority::RenderingPriority getRenderingPriority() const override;

    protected:
        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;
    };
}

#endif // TENGINE_EMPTYRENDERINGSTRATEGY_H