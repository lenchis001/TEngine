#include "Components/Graphics/Rendering/Services/Scene/RenderingStrategies/RenderingStrategyBase.h"

#include <memory>

#include "Components/Graphics/Rendering/Services/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Services/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Services/Textures/ITexturesService.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Services::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Services::Textures;

namespace TEngine::Components::Graphics::Rendering::Services::Scene::RenderingStrategies::Solid
{
    class SolidboxRenderingStrategy : public RenderingStrategyBase
    {
    public:
        SolidboxRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::string texturePath,
            const Vector3df size);
        ~SolidboxRenderingStrategy() override;

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        std::vector<float> getVertices() const override;

        std::type_index getType() const override;

    protected:
        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;

    private:
        Vector3df _size;

        bool _isVisualAttached;

        std::shared_ptr<IRenderingStrategy> _visual;
    };
}