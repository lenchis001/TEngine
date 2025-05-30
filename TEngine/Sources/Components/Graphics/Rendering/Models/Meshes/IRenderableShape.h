#ifndef IRENDERABLE_SHAPE_H
#define IRENDERABLE_SHAPE_H

#include "vector"
#include "string"

#include "Components/Graphics/PlatformWrapping/GlWrapper.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class IRenderableShape
    {
    public:
        virtual ~IRenderableShape() = default;

        virtual const std::string& getName() = 0;
        
        virtual GLuint getVAO() const = 0;

        virtual GLuint getIndexBuffer() const = 0;

        virtual GLuint getProgram() const = 0;

        virtual GLuint getMvpMatrixShaderId() const = 0;

        virtual GLuint getShapeColorShaderId() const = 0;

        virtual const std::vector<float>& getDiffuseColor() const = 0;

        virtual GLuint getTextureId() const = 0;

        virtual const std::vector<float>& getVertices() const = 0;

        virtual bool isTextured() const = 0;
    };
}

#endif // IRENDERABLE_SHAPE_H