#include "SkySphereRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Sky;

SkySphereRenderingStrategy::SkySphereRenderingStrategy(std::shared_ptr<IShadersService> shadersService,
                                                       std::shared_ptr<IBuffersService> bufferCacheService,
                                                       std::shared_ptr<ITexturesService> texturesService)
{
}

void SkySphereRenderingStrategy::setTexture(const std::string &texturePath)
{
}

void SkySphereRenderingStrategy::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
}