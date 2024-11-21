#ifndef TENGINE_RENDERINGOPTIMIZATIONMIXIN_H
#define TENGINE_RENDERINGOPTIMIZATIONMIXIN_H

#include <memory>

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/IRenderingStrategy.h"
#include "Components/Graphics/Rendering/Scene/CameraStrategies/ICameraStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingMixins
{
    class RenderingOptimizationMixin : public virtual IRenderingStrategy
    {
    public:
        RenderingOptimizationMixin();

    protected:
        bool _isRenderingSkipAllowed(std::shared_ptr<ICameraStrategy> activeCameraStrategy);

    private:
        unsigned int _frameCounter;
        float _distance;
    };
}

#endif //TENGINE_RENDERINGOPTIMIZATIONMIXIN_H