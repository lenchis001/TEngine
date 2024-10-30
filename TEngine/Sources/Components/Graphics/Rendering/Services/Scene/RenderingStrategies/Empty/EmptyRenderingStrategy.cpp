#include "EmptyRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Empty;

std::vector<float> EmptyRenderingStrategy::getVertices() const {
    return std::vector<float>();
}

std::type_index EmptyRenderingStrategy::getType() const {
    return typeid(EmptyRenderingStrategy);
}