#ifndef TENGINE_MESHLOADING_MODELS_IMESH_H
#define TENGINE_MESHLOADING_MODELS_IMESH_H

#include "memory"
#include "vector"

#include "IShape.h"

namespace TEngine::Components::Graphics::MeshLoading::Models
{
    class IMesh
    {
    public:
        virtual ~IMesh() = default;
        
        virtual const std::vector<std::shared_ptr<IShape>> &getShapes() const = 0;
    };
}

#endif // TENGINE_MESHLOADING_MODELS_IMESH_H