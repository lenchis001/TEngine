#include "EmptyRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Empty;

std::type_index EmptyRenderingStrategy::getType() const
{
    return typeid(EmptyRenderingStrategy);
}

std::string EmptyRenderingStrategy::_getDefaultName() const
{
    return "Empty";
}

void EmptyRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
}