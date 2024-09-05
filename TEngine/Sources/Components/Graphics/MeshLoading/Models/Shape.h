#ifndef TENGINE_MESH_LOADING_MODELS_SHAPE_H
#define TENGINE_MESH_LOADING_MODELS_SHAPE_H

#include "IShape.h"

namespace TEngine::Components::Graphics::MeshLoading::Models
{
    class Shape : public IShape
    {
    public:
        Shape(
            const std::string &name,
            const std::vector<float> &vertices,
            const std::vector<std::string> &textures,
            const std::vector<float> &normals,
            const std::vector<float> &uvs);

        const std::string &getName() const override;

        const std::vector<float> &getVertices() const override;

        const std::vector<std::string> &getTextures() const override;

        const std::vector<float> &getNormals() const override;

        const std::vector<float> &getUVs() const override;

    private:
        std::string _name;
        std::vector<float> _vertices;
        std::vector<std::string> _textures;
        std::vector<float> _normals;
        std::vector<float> _uvs;
    };
}

#endif // TENGINE_MESH_LOADING_MODELS_SHAPE_H