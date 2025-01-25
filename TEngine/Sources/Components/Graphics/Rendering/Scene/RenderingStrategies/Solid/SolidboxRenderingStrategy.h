#include <memory>

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Physics/PhysicsRenderingStrategyBase.h"
#include "ISolidboxRenderingStrategy.h"

#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Scene/Physics/IPhysicsService.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Priority;
using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Scene::Physics;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Solid
{
    class SolidboxRenderingStrategy : public PhysicsRenderingStrategyBase, public ISolidboxRenderingStrategy
    {
    public:
        SolidboxRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<IPhysicsService> physicsService,
            OnDeleteCallback onDeleteCallback);
        ~SolidboxRenderingStrategy() override;

        std::type_index getType() const override;

        void setIsVisualizationEnabled(bool value) override;

        RenderingPriority getRenderingPriority() const override;

    protected:
        std::vector<float> _getVertices() const override;

        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    private:
        void _prepareVertexVbo();
        void _prepareVao();
        void _prepareShader();

        bool _isVisualizationEnabled;

        GLuint _vao, _shaderProgram, _matrixShaderId;

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;

        static std::vector<float> _vertices;
    };
}