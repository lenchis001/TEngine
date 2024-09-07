#include "RenderableMesh.h"

using namespace TEngine::Components::Graphics::Rendering::Models::Meshes;

RenderableMesh::RenderableMesh(const std::vector<std::shared_ptr<IRenderableShape>>& shapes)
    : _shapes(shapes)
{
}

const std::vector<std::shared_ptr<IRenderableShape>>& RenderableMesh::getShapes() const
{
    return _shapes;
}