#include "vector"

#include "Components/Graphics/Models/Vector3d.h"
#include "Components/Graphics/Models/Vector2d.h"

namespace TEngine::Components::Graphics::MeshLoading::Models::Plugins
{
    class IStaticMesh
    {
    public:
        virtual ~IStaticMesh() = default;

        virtual const std::vector<Vector3df> &getVertices() const = 0;

        virtual const std::vector<std::wstring> &getTextures() const = 0;

        virtual const std::vector<Vector3df> &getNormals() const = 0;

        virtual const std::vector<Vector2df> &getUVs() const = 0;
    };
}