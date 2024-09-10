#include "RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

RenderableShape::RenderableShape(
    std::string name,
    GLuint vao,
    unsigned int verticesCount,
    GLuint program,
    GLuint mvpMatrixShaderId,
    GLuint modelMatrixShaderId,
    GLuint viewMatrixShaderId,
    GLuint lightPosShaderId,
    GLuint lightColorShaderId,
    GLuint lightPowerShaderId,
    GLuint shapeColorShaderId,
    const std::vector<float>& diffuseColor)
    : _name(name),
      _vao(vao),
      _verticesCount(verticesCount),
      _program(program),
      _mvpMatrixShaderId(mvpMatrixShaderId),
      _modelMatrixShaderId(modelMatrixShaderId),
      _viewMatrixShaderId(viewMatrixShaderId),
      _lightPosShaderId(lightPosShaderId),
      _lightColorShaderId(lightColorShaderId),
      _lightPowerShaderId(lightPowerShaderId),
      _shapeColorShaderId(shapeColorShaderId),
      _diffuseColor(diffuseColor)
{
}

const std::string &RenderableShape::getName() const
{
    return _name;
}

GLuint RenderableShape::getVAO() const
{
    return _vao;
}

GLuint RenderableShape::getProgram() const
{
    return _program;
}

GLuint RenderableShape::getMvpMatrixShaderId() const
{
    return _mvpMatrixShaderId;
}

GLuint RenderableShape::getModelMatrixShaderId() const
{
    return _modelMatrixShaderId;
}

GLuint RenderableShape::getViewMatrixShaderId() const
{
    return _viewMatrixShaderId;
}

GLuint RenderableShape::getLightPosShaderId() const
{
    return _lightPosShaderId;
}

GLuint RenderableShape::getLightColorShaderId() const
{
    return _lightColorShaderId;
}

GLuint RenderableShape::getLightPowerShaderId() const
{
    return _lightPowerShaderId;
}

GLuint RenderableShape::getShapeColorShaderId() const
{
    return _shapeColorShaderId;
}

const std::vector<float> &RenderableShape::getDiffuseColor() const
{
    return _diffuseColor;
}

unsigned int RenderableShape::getVerticesCount() const
{
    return _verticesCount;
}