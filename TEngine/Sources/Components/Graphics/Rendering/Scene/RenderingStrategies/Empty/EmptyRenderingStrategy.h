#ifndef TENGINE_EMPTYRENDERINGSTRATEGY_H
#define TENGINE_EMPTYRENDERINGSTRATEGY_H

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Empty
{
    class EmptyRenderingStrategy : public RenderingStrategyBase
    {
    public:
        std::vector<float> getVertices() const override;

        std::type_index getType() const override;

    protected:
        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;
    };
}

#endif // TENGINE_EMPTYRENDERINGSTRATEGY_H