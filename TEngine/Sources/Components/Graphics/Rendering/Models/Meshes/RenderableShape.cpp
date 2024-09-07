#include "RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

RenderableShape::RenderableShape(GLuint vao, unsigned int verticesCount)
    : _vao(vao), _verticesCount(verticesCount)
{
}

GLuint RenderableShape::getVAO() const
{
    return _vao;
}

unsigned int RenderableShape::getVerticesCount() const
{
    return _verticesCount;
}