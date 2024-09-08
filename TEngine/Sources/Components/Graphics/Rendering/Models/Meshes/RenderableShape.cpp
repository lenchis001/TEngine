#include "RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

RenderableShape::RenderableShape(GLuint vao, unsigned int verticesCount, GLuint program, GLuint mvpShaderId)
    : _vao(vao), _verticesCount(verticesCount), _program(program), _mvpShaderId(mvpShaderId)
{
}

GLuint RenderableShape::getVAO() const
{
    return _vao;
}

GLuint RenderableShape::getProgram() const
{
    return _program;
}

GLuint RenderableShape::getMvpShaderId() const
{
    return _mvpShaderId;
}

unsigned int RenderableShape::getVerticesCount() const
{
    return _verticesCount;
}