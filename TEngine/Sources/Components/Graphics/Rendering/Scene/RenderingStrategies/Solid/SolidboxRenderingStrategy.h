#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include <memory>

#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid
{
    class SolidboxRenderingStrategy : public RenderingStrategyBase
    {
    public:
        SolidboxRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::string texturePath);
        ~SolidboxRenderingStrategy() override;

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        std::vector<float> getVertices() const override;

        std::type_index getType() const override;

    protected:
        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;

        std::string _getDefaultName() const override;

    private:
        bool _isVisualAttached;

        std::shared_ptr<IRenderingStrategy> _visual;
    };
}