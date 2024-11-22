#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include <memory>

#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"
#include "Components/Graphics/Rendering/Scene/Physics/IPhysicsService.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid
{
    class SolidboxRenderingStrategy : public RenderingStrategyBase
    {
    public:
        SolidboxRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::shared_ptr<IPhysicsService> physicsService,
            std::string texturePath);
        ~SolidboxRenderingStrategy() override;

        std::type_index getType() const override;

    protected:
        //std::vector<float> getVertices() const override;

        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;

        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    private:
        bool _isVisualAttached;

        std::shared_ptr<IRenderingStrategy> _visual;
    };
}