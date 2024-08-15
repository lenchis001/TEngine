#ifndef TENGINE_RENDERABLE_OBJECT_BASE_H
#define TENGINE_RENDERABLE_OBJECT_BASE_H

#include "IRenderableObject.h"

using namespace TEngine::Components::Graphics::Models;

namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects
{
    class RenderableObjectBase : public IRenderableObject
    {
    public:
        RenderableObjectBase();
        RenderableObjectBase(const Vector3df& position, const Vector3df& rotation, const Vector3df& scale);
        virtual ~RenderableObjectBase();

        const std::vector<std::shared_ptr<IRenderableObject>>& getChildren() const override;
        void addChild(std::shared_ptr<IRenderableObject> child) override;
        void removeChild(std::shared_ptr<IRenderableObject> child) override;

        void setPosition(const Vector3df& position) override;
        void setRotation(const Vector3df& rotation) override;
        void setScale(const Vector3df& scale) override;

        Vector3df getPosition() const override;
        Vector3df getRotation() const override;
        Vector3df getScale() const override;

        const Matrix4x4f& getTransformationMatrix() const override;
    private:
        void _updateTransformationMatrix(const Matrix4x4f& parentMatrix) override;

        Vector3df _position;
        Vector3df _rotation;
        Vector3df _scale;

        Matrix4x4f _transformationMatrix;

        std::vector<std::shared_ptr<IRenderableObject>> _children;
    };
}

#endif //TENGINE_RENDERABLE_OBJECT_BASE_H