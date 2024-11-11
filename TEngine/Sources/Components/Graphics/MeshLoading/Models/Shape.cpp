#include "Shape.h"

using namespace TEngine::Components::Graphics::MeshLoading::Models;

Shape::Shape(
    const std::string &name,
    const std::vector<float> &vertices,
    const std::vector<float> &normals,
    const std::vector<float> &uvs,
    const std::vector<float> &diffuseColor,
    const std::string &texturePath)
    : _name(name),
      _vertices(vertices),
      _normals(normals),
      _uvs(uvs),
      _diffuseColor(diffuseColor),
      _texturePath(texturePath)
{
}

const std::string &Shape::getName()
{
    return _name;
}

const std::vector<float> &Shape::getVertices() const
{
    return _vertices;
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

const std::string &Shape::getTexturePath() const
{
    return _texturePath;
}

bool Shape::isTextured() const
{
    return !_uvs.empty() && !_texturePath.empty();
}