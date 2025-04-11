#ifndef TENGINE_CUBE_RENDERING_STRATEGY_H
#define TENGINE_CUBE_RENDERING_STRATEGY_H

#include <memory>

#ifdef __ANDROID__
#include <EGL/egl.h>
#else
#include <GL/gl.h>
#endif

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/RenderingStrategyBase.h"
#include "Components/Graphics/Rendering/Scene/Shaders/IShadersService.h"
#include "Components/Graphics/ImageLoading/Models/Image.h"
#include "Components/Graphics/Rendering/Scene/Buffers/IBuffersService.h"
#include "Components/Graphics/Rendering/Textures/ITexturesService.h"
#include "Components/Graphics/Rendering/Scene/Physics/IPhysicsService.h"

#include "Components/Graphics/Rendering/Scene/RenderingStrategies/Physics/PhysicsRenderingStrategyBase.h"

#include "ICubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Models::Priority;
using namespace TEngine::Components::Graphics::Rendering::Scene::Shaders;
using namespace TEngine::Components::Graphics::ImageLoading::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::Buffers;
using namespace TEngine::Components::Graphics::Rendering::Textures;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingMixins;
using namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Physics;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies::Primitives
{
    class CubeRenderingStrategy : public PhysicsRenderingStrategyBase, public ICubeRenderingStrategy
    {
    public:
        CubeRenderingStrategy(
            std::shared_ptr<IShadersService> shadersService,
            std::shared_ptr<IBuffersService> bufferCacheService,
            std::shared_ptr<ITexturesService> texturesService,
            std::shared_ptr<IPhysicsService> physicsService,
            OnDeleteCallback onDeleteCallback);
        ~CubeRenderingStrategy() override;

        std::type_index getType() const override;

        void setPosition(const Vector3df &position) override;

        void setRotation(const Vector3df &rotation) override;

        const std::string &getTexture() const override;

        void setTexture(const std::string &texturePath) override;

        RenderingPriority getRenderingPriority() const override;

    protected:
        std::string _getDefaultName() const override;

        void _renderSafe(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

        std::vector<float> _getVertices() const override;

        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;

        void _onDetachedFromParent() override;

    private:
        void _prepareVertexVbo();
        void _prepareUvVbo();
        void _prepareVao();
        void _prepareShader();

        std::shared_ptr<IShadersService> _shadersService;
        std::shared_ptr<IBuffersService> _bufferCacheService;
        std::shared_ptr<ITexturesService> _texturesService;

        GLuint _shaderProgram, _matrixShaderId, _textureId, _textureSamplerShaderId, _vao;

        std::string _texturePath;

        static std::vector<float> _vertices;
    };
}

#endif // TENGINE_CUBE_RENDERING_STRATEGY_H