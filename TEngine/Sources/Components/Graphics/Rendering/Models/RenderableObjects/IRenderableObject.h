#ifndef TENGINE_IRENDERABLEOBJECT_H
#define TENGINE_IRENDERABLEOBJECT_H

#include "memory"
#include "vector"

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Models/Matrix4x4.h"
#include "Components/Graphics/Rendering/Models/RenderableObjects/IRenderableObject.h"

namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects
{
    class RenderableObjectBase;

    class IRenderableObject
    {
    public:
        virtual void setPosition(const Graphics::Models::Vector3df &position) = 0;
        virtual void setRotation(const Graphics::Models::Vector3df &rotation) = 0;
        virtual void setScale(const Graphics::Models::Vector3df &scale) = 0;

        virtual Graphics::Models::Vector3df getPosition() const = 0;
        virtual Graphics::Models::Vector3df getRotation() const = 0;
        virtual Graphics::Models::Vector3df getScale() const = 0;

        virtual const std::vector<std::shared_ptr<IRenderableObject>> &getChildren() const = 0;
        virtual void addChild(std::shared_ptr<IRenderableObject> child) = 0;
        virtual void removeChild(std::shared_ptr<IRenderableObject> child) = 0;

        virtual const Graphics::Models::Matrix4x4f &getTransformationMatrix() const = 0;

        virtual ~IRenderableObject() = default;

        friend class RenderableObjectBase;

    protected:
        virtual void _updateTransformationMatrix(const Graphics::Models::Matrix4x4f &parentMatrix) = 0;
    };
}

#endif // TENGINE_IRENDERABLEOBJECT_H