#include "RenderingOptimizationMixin.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingMixins;

RenderingOptimizationMixin::RenderingOptimizationMixin()
    : _frameCounter(0),
      _distance(0.f)
{
}

bool RenderingOptimizationMixin::_isRenderingSkipAllowed(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    if ((_frameCounter % 30) == 0)
    {
        const auto &cameraPosition = activeCameraStrategy->getPosition();
        _distance = cameraPosition.distance(getAbsolutePosition());
    }

    _frameCounter++;

    return _distance > 100.f;
}