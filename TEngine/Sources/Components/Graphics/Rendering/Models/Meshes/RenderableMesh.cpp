#include "RenderableMesh.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

RenderableMesh::RenderableMesh(
    const std::string &source,
    const std::vector<std::shared_ptr<IRenderableShape>> &shapes)
    : _source(source),
      _shapes(shapes)
{
}

const std::string &RenderableMesh::getSource() const
{
    return _source;
}

const std::vector<std::shared_ptr<IRenderableShape>> &RenderableMesh::getShapes() const
{
    return _shapes;
}