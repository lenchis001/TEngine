#include "Shape.h"

using namespace TEngine::Components::Graphics::MeshLoading::Models;

Shape::Shape(
    const std::string &name,
    const std::vector<float> &vertices,
    const std::vector<std::string> &textures,
    const std::vector<float> &normals,
    const std::vector<float> &uvs,
    const std::vector<float> &diffuseColor)
    : _name(name),
      _vertices(vertices),
      _textures(textures),
      _normals(normals),
      _uvs(uvs),
      _diffuseColor(diffuseColor)
{
}

const std::string &Shape::getName() const
{
    return _name;
}

const std::vector<float> &Shape::getVertices() const
{
    return _vertices;
}

const std::vector<std::string> &Shape::getTextures() const
{
    return _textures;
}

const std::vector<float> &Shape::getNormals() const
{
    return _normals;
}

const std::vector<float> &Shape::getUVs() const
{
    return _uvs;
}

const std::vector<float> &Shape::getDiffuseColor() const
{
    return _diffuseColor;
}