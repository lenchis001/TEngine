#include "IMesh.h"

namespace TEngine::Components::Graphics::MeshLoading::Models
{
    class Mesh : public IMesh
    {
    public:
        Mesh(const std::vector<std::shared_ptr<IShape>> &shapes);
        ~Mesh() override = default;

        const std::vector<std::shared_ptr<IShape>> &getShapes() const override;

    private:
        std::vector<std::shared_ptr<IShape>> _shapes;
    };
}