#ifndef TENGINE_IMESHRENDERABLEOBJECT_H
#define TENGINE_IMESHRENDERABLEOBJECT_H

#include "IRenderableObject.h"

namespace TEngine::Components::Graphics::Rendering::Models::RenderableObjects
{
    class IMeshRenderableObject : IRenderableObject
    {
    public:
        virtual ~IMeshRenderableObject() = default;
    };
}

#endif //TENGINE_IMESHRENDERABLEOBJECT_H