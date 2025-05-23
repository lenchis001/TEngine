#ifndef IRENDERABLE_MESH_H
#define IRENDERABLE_MESH_H

#include "memory"
#include "vector"
#include "string"

#include "IRenderableShape.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class IRenderableMesh
    {
    public:
        virtual ~IRenderableMesh() = default;

        virtual const std::string& getSource() const = 0;

        virtual const std::vector<std::shared_ptr<IRenderableShape>>& getShapes() const = 0;
    };
}

#endif // IRENDERABLE_MESH_H