#ifndef TENGINE_RENDERINGSTRATEGYBASE_H
#define TENGINE_RENDERINGSTRATEGYBASE_H

#include "IRenderingStrategy.h"

#include <memory>
#include <vector>

#include "Components/Graphics/Models/Vector3d.h"

using namespace TEngine::Components::Graphics::Models;
using namespace TEngine::Components::Graphics::Rendering::Scene::CameraStrategies;

namespace TEngine::Components::Graphics::Rendering::Scene::RenderingStrategies
{
    class RenderingStrategyBase : public std::enable_shared_from_this<IRenderingStrategy>, public IRenderingStrategy
    {
    public:
        RenderingStrategyBase();
        ~RenderingStrategyBase();

        const std::vector<std::shared_ptr<IRenderingStrategy>> &getChildren() const override;
        void addChild(std::shared_ptr<IRenderingStrategy> child) override;
        void removeChild(std::shared_ptr<IRenderingStrategy> child) override;
        void removeAllChildren() override;

        void setPosition(const Vector3df &position) override;
        void setRotation(const Vector3df &rotation) override;
        void setScale(const Vector3df &scale) override;

        const Vector3df &getPosition() const override;
        const Vector3df &getRotation() const override;
        const Vector3df &getScale() const override;

        void setAbsolutePosition(const Vector3df &position) override;
        void setAbsoluteRotation(const Vector3df &rotation) override;

        Vector3df getAbsolutePosition() const override;
        Vector3df getAbsoluteRotation() const override;
        Vector3df getAbsoluteScale() const override;

        void render(std::shared_ptr<ICameraStrategy> activeCameraStrategy) override;

    protected:
        const Matrix4x4f &getModelMatrix() const override;

        void _updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated = false) final;

        void _onAttachedToParent(std::shared_ptr<IRenderingStrategy> parent) override;
        void _onDetachedFromParent() override;

        inline const Matrix4x4f &getMvpMatrix() const {
            return _mvpMatrix;
        }

    private:
        void _updateTranslationMatrix();
        void _updateRotationMatrix();
        void _updateScaleMatrix();
        void _updateMvpMatrix();

        Vector3df _position;
        Vector3df _rotation;
        Vector3df _scale;

        Matrix4x4f _translationMatrix, _rotationMatrix, _scaleMatrix;
        Matrix4x4f _modelMatrix;
        Matrix4x4f _parentMatrix;
        Matrix4x4f _vpMatrix, _mvpMatrix;

        std::vector<std::shared_ptr<IRenderingStrategy>> _children;
    };
}

#endif // TENGINE_RENDERINGSTRATEGYBASE_H