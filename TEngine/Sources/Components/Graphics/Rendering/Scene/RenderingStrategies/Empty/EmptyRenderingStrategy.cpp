#include "EmptyRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Priority;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Empty;

EmptyRenderingStrategy::EmptyRenderingStrategy(OnDeleteCallback onDeleteCallback)
    : RenderingStrategyBase(onDeleteCallback)
{
}

std::type_index EmptyRenderingStrategy::getType() const
{
    return typeid(EmptyRenderingStrategy);
}

RenderingPriority EmptyRenderingStrategy::getRenderingPriority() const
{
    return RenderingPriority::NONE;
}

std::string EmptyRenderingStrategy::_getDefaultName() const
{
    return "Empty";
}

void EmptyRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
}