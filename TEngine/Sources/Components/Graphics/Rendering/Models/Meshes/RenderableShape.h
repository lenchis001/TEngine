#ifndef RENDERABLE_SHAPE_H
#define RENDERABLE_SHAPE_H

#include "IRenderableShape.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class RenderableShape : public IRenderableShape
    {
    public:
        RenderableShape(GLuint vao, unsigned int verticesCount);
        ~RenderableShape() = default;

        GLuint getVAO() const override;

        unsigned int getVerticesCount() const override;

    private:
        GLuint _vao;
        unsigned int _verticesCount;
    };
}

#endif // RENDERABLE_SHAPE_H