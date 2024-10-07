#include "SolidboxRenderingStrategy.h"

#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/Primitives/CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Primitives;

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Solid;

SolidboxRenderingStrategy::SolidboxRenderingStrategy(
    std::shared_ptr<IShadersService> shadersService,
    std::shared_ptr<IBuffersService> bufferCacheService,
    std::shared_ptr<ITexturesService> texturesService,
    std::string texturePath,
    const Vector3df size)
    : RenderingStrategyBase(),
      _size(size),
      _isVisualAttached(false)
{
    _visual = std::make_shared<CubeRenderingStrategy>(shadersService, bufferCacheService, texturesService, texturePath);

    // We need divide by 2 because the cube size is 2x2x2
    _visual->setScale(size / 2);
}

SolidboxRenderingStrategy::~SolidboxRenderingStrategy()
{
}

void SolidboxRenderingStrategy::render(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
    RenderingStrategyBase::render(activeCameraStrategy);
}

std::vector<float> SolidboxRenderingStrategy::getVertices() const
{
    return {
        // bottom corner
        -_size.getX() / 2,
        -_size.getY() / 2,
        -_size.getZ() / 2,
        // top corner
        _size.getX() / 2,
        _size.getY() / 2,
        _size.getZ() / 2,
    };
}

void SolidboxRenderingStrategy::_onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent)
{
    if (!_isVisualAttached)
    {
        _isVisualAttached = true;

        addChild(_visual);
    }

    RenderingStrategyBase::_onAttachedToParent(parent);
}