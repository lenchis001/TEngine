#include "RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

RenderableShape::RenderableShape(
    std::string name,
    GLuint vao,
    GLuint indexBuffer,
    const std::vector<float> vertices,
    GLuint program,
    GLuint mvpMatrixShaderId,
    GLuint shapeColorShaderId,
    const std::vector<float> &diffuseColor,
    GLuint textureId)
    : _name(name),
      _vao(vao),
      _indexBuffer(indexBuffer),
      _vertices(vertices),
      _program(program),
      _mvpMatrixShaderId(mvpMatrixShaderId),
      _shapeColorShaderId(shapeColorShaderId),
      _diffuseColor(diffuseColor),
      _textureId(textureId)
{
}

const std::string &RenderableShape::getName()
{
    return _name;
}

bool RenderableShape::isTextured() const
{
    return _textureId != 0;
}