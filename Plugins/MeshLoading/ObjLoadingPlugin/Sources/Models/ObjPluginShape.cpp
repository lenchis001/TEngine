#include "ObjPluginShape.h"

using namespace ObjLoadingPlugin::Models;

ObjPluginShape::ObjPluginShape(
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

const std::string &ObjPluginShape::getName() const
{
    return _name;
}

const std::vector<float> &ObjPluginShape::getVertices() const
{
    return _vertices;
}

const std::vector<std::string> &ObjPluginShape::getTextures() const
{
    return _textures;
}

const std::vector<float> &ObjPluginShape::getNormals() const
{
    return _normals;
}

const std::vector<float> &ObjPluginShape::getUVs() const
{
    return _uvs;
}

const std::vector<float> &ObjPluginShape::getDiffuseColor() const
{
    return _diffuseColor;
}