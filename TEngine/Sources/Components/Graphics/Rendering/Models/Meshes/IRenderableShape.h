#ifndef IRENDERABLE_SHAPE_H
#define IRENDERABLE_SHAPE_H

#include "glfw/glfw3.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class IRenderableShape
    {
    public:
        virtual ~IRenderableShape() = default;
        
        virtual GLuint getVAO() const = 0;

        virtual unsigned int getVerticesCount() const = 0;
    };
}

#endif // IRENDERABLE_SHAPE_H