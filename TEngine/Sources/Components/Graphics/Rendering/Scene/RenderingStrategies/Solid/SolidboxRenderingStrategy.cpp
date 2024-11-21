#include "SolidboxRenderingStrategy.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Primitives/CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives;

using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid;

SolidboxRenderingStrategy::SolidboxRenderingStrategy(
    std::shared_ptr<IShadersService> shadersService,
    std::shared_ptr<IBuffersService> bufferCacheService,
    std::shared_ptr<ITexturesService> texturesService,
    std::string texturePath)
    : RenderingStrategyBase(),
      _isVisualAttached(false)
{
    _visual = std::make_shared<CubeRenderingStrategy>(shadersService, bufferCacheService, texturesService, texturePath);
}

SolidboxRenderingStrategy::~SolidboxRenderingStrategy()
{
}

std::vector<float> SolidboxRenderingStrategy::getVertices() const
{
    auto& size = _visual->getScale();


    return {
        // bottom corner
        -size.getX(),
        -size.getY(),
        -size.getZ(),
        // top corner
        size.getX(),
        size.getY(),
        size.getZ(),
    };
}

std::type_index SolidboxRenderingStrategy::getType() const
{
    return typeid(SolidboxRenderingStrategy);
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

std::string SolidboxRenderingStrategy::_getDefaultName() const
{
    return "Solidbox";
}

void SolidboxRenderingStrategy::_renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy)
{
}