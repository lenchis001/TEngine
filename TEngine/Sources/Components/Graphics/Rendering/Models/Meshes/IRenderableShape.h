#ifndef IRENDERABLE_SHAPE_H
#define IRENDERABLE_SHAPE_H

#include "vector"
#include "string"

#include "GLFW/glfw3.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class IRenderableShape
    {
    public:
        virtual ~IRenderableShape() = default;

        virtual const std::string& getName() const = 0;
        
        virtual GLuint getVAO() const = 0;

        virtual GLuint getProgram() const = 0;

        virtual GLuint getMvpMatrixShaderId() const = 0;

        virtual GLuint getModelMatrixShaderId() const = 0;

        virtual GLuint getViewMatrixShaderId() const = 0;

        virtual GLuint getLightPosShaderId() const = 0;

        virtual GLuint getLightColorShaderId() const = 0;

        virtual GLuint getLightPowerShaderId() const = 0;

        virtual GLuint getShapeColorShaderId() const = 0;

        virtual const std::vector<float>& getDiffuseColor() const = 0;

        virtual GLuint getTextureId() const = 0;

        virtual const std::vector<float>& getVertices() const = 0;

        virtual bool isTextured() const = 0;
    };
}

#endif // IRENDERABLE_SHAPE_H