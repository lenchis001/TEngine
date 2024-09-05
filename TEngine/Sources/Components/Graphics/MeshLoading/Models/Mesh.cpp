#include "Mesh.h"

using namespace TEngine::Components::Graphics::MeshLoading::Models;

Mesh::Mesh(const std::vector<std::shared_ptr<IShape>> &shapes)
    : _shapes(shapes)
{
}

const std::vector<std::shared_ptr<IShape>> &Mesh::getShapes() const
{
    return _shapes;
}