#ifndef TENGINE_RENDERINGSTRATEGYBASE_H
#define TENGINE_RENDERINGSTRATEGYBASE_H

#include "IRenderingStrategy.h"

#include "vector"

#include "Components/Graphics/Models/Vector3d.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies
{
    class RenderingStrategyBase : public IRenderingStrategy
    {
    public:
        RenderingStrategyBase();

        const std::vector<std::shared_ptr<IRenderingStrategy>> &getChildren() const override;
        void addChild(std::shared_ptr<IRenderingStrategy> child) override;
        void removeChild(std::shared_ptr<IRenderingStrategy> child) override;

        void setPosition(const Vector3df &position) override;
        void setRotation(const Vector3df &rotation) override;
        void setScale(const Vector3df &scale) override;

        const Vector3df &getPosition() const override;
        const Vector3df &getRotation() const override;
        const Vector3df &getScale() const override;

        Vector3df getAbsolutePosition() override;

        const Parallelepipedf &getVerticesCude() const override;

        void render(
            const Matrix4x4f &vpMatrix,
            const Parallelepipedf &viewArea) override;

    protected:
        inline const Matrix4x4f &getModelMatrix() const
        {
            return _modelMatrix;
        }

        inline const Matrix4x4f &getMvpMatrix() const
        {
            return _mvpMatrix;
        }

        void _updateModelMatrix(const Matrix4x4f &parentMatrix, bool isPrsUpdated = false) final;

    private:
        void _updateTranslationMatrix();
        void _updateRotationMatrix();
        void _updateScaleMatrix();
        void _updateMvpMatrix();

        void _updateVerticesCube();

        Vector3df _position;
        Vector3df _rotation;
        Vector3df _scale;

        Matrix4x4f _translationMatrix, _rotationMatrix, _scaleMatrix;
        Matrix4x4f _modelMatrix;
        Matrix4x4f _parentMatrix;
        Matrix4x4f _vpMatrix, _mvpMatrix;

        Parallelepipedf _verticesCube;

        std::vector<std::shared_ptr<IRenderingStrategy>> _children;
    };
}

#endif // TENGINE_RENDERINGSTRATEGYBASE_H