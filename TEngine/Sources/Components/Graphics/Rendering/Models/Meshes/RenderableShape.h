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
            GLuint indexBuffer,
            const std::vector<float> vertices,
            GLuint program,
            GLuint mvpMatrixShaderId,
            GLuint modelMatrixShaderId,
            GLuint viewMatrixShaderId,
            GLuint lightPosShaderId,
            GLuint lightColorShaderId,
            GLuint lightPowerShaderId,
            GLuint shapeColorShaderId,
            const std::vector<float> &diffuseColor,
            GLuint textureId);
        ~RenderableShape() = default;

        const std::string &getName() override;

        inline GLuint getVAO() const override {
            return _vao;
        }

        inline GLuint getIndexBuffer() const override {
            return _indexBuffer;
        }

        inline GLuint getProgram() const override {
            return _program;
        }

        inline GLuint getMvpMatrixShaderId() const override {
            return _mvpMatrixShaderId;
        }

        inline GLuint getModelMatrixShaderId() const override {
            return _modelMatrixShaderId;
        }

        inline GLuint getViewMatrixShaderId() const override {
            return _viewMatrixShaderId;
        }

        inline GLuint getLightPosShaderId() const override {
            return _lightPosShaderId;
        }

        inline GLuint getLightColorShaderId() const override {
            return _lightColorShaderId;
        }

        inline GLuint getLightPowerShaderId() const override {
            return _lightPowerShaderId;
        }

        inline GLuint getShapeColorShaderId() const override {
            return _shapeColorShaderId;
        }

        inline const std::vector<float> &getDiffuseColor() const override {
            return _diffuseColor;
        }

        inline const std::vector<float>& getVertices() const override {
            return _vertices;
        }

        inline GLuint getTextureId() const override {
            return _textureId;
        }

        inline bool isTextured() const override;

    private:
        std::string _name;
        GLuint _vao;
        GLuint _indexBuffer;
        GLuint _program;
        GLuint _mvpMatrixShaderId;
        GLuint _modelMatrixShaderId;
        GLuint _viewMatrixShaderId;
        GLuint _lightPosShaderId;
        GLuint _lightColorShaderId;
        GLuint _lightPowerShaderId;
        GLuint _shapeColorShaderId;
        std::vector<float> _diffuseColor;
        GLuint _textureId;
        std::vector<float> _vertices;
    };
}

#endif // RENDERABLE_SHAPE_H