#ifndef RENDERABLE_SHAPE_H
#define RENDERABLE_SHAPE_H

#include "IRenderableShape.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class RenderableShape : public IRenderableShape
    {
    public:
        RenderableShape(GLuint vao, unsigned int verticesCount, GLuint program, GLuint mvpShaderId);
        ~RenderableShape() = default;

        GLuint getVAO() const override;

        GLuint getProgram() const override;

        GLuint getMvpShaderId() const override;

        unsigned int getVerticesCount() const override;

    private:
        GLuint _vao;
        GLuint _program;
        GLuint _mvpShaderId;
        unsigned int _verticesCount;
    };
}

#endif // RENDERABLE_SHAPE_H