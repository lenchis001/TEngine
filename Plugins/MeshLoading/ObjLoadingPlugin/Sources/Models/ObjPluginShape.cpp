#include "ObjPluginShape.h"

using namespace ObjLoadingPlugin::Models;

ObjPluginShape::ObjPluginShape(
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

const std::string &ObjPluginShape::getName() const
{
    return _name;
}

const std::vector<float> &ObjPluginShape::getVertices() const
{
    return _vertices;
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

const std::string &ObjPluginShape::getTexturePath() const
{
    return _texturePath;
}