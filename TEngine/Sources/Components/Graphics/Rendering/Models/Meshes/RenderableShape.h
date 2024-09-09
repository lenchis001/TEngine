#ifndef RENDERABLE_SHAPE_H
#define RENDERABLE_SHAPE_H

#include "IRenderableShape.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class RenderableShape : public IRenderableShape
    {
    public:
        RenderableShape(
            std::string name,
            GLuint vao,
            unsigned int verticesCount,
            GLuint program,
            GLuint mvpMatrixShaderId,
            GLuint modelMatrixShaderId,
            GLuint viewMatrixShaderId,
            GLuint lightPosShaderId,
            GLuint lightColorShaderId,
            GLuint lightPowerShaderId);
        ~RenderableShape() = default;

        const std::string &getName() const override;

        GLuint getVAO() const override;

        GLuint getProgram() const override;

        GLuint getMvpMatrixShaderId() const override;

        GLuint getModelMatrixShaderId() const override;

        GLuint getViewMatrixShaderId() const override;

        GLuint getLightPosShaderId() const override;

        GLuint getLightColorShaderId() const override;

        GLuint getLightPowerShaderId() const override;

        unsigned int getVerticesCount() const override;

    private:
        std::string _name;
        GLuint _vao;
        GLuint _program;
        GLuint _mvpMatrixShaderId;
        GLuint _modelMatrixShaderId;
        GLuint _viewMatrixShaderId;
        GLuint _lightPosShaderId;
        GLuint _lightColorShaderId;
        GLuint _lightPowerShaderId;
        unsigned int _verticesCount;
    };
}

#endif // RENDERABLE_SHAPE_H