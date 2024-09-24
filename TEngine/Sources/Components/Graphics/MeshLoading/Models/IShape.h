#ifndef TENGINE_MESH_LOADING_ISHAPE_H
#define TENGINE_MESH_LOADING_ISHAPE_H

#include "string"
#include "vector"

namespace TEngine::Components::Graphics::MeshLoading::Models
{
    class IShape
    {
    public:
        virtual ~IShape() = default;

        virtual const std::string &getName() const = 0;

        virtual const std::vector<float> &getVertices() const = 0;

        virtual const std::vector<float> &getNormals() const = 0;

        virtual const std::vector<float> &getUVs() const = 0;

        virtual const std::vector<float> &getDiffuseColor() const = 0;

        virtual const std::string &getTexturePath() const = 0;

        virtual bool isTextured() const = 0;
    };
}

#endif // TENGINE_MESH_LOADING_ISHAPE_H