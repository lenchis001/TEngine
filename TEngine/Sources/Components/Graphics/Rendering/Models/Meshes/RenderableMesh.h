#include "IRenderableMesh.h"

namespace TEngine::Components::Graphics::Rendering::Models::Meshes
{
    class RenderableMesh : public IRenderableMesh
    {
    public:
        RenderableMesh(const std::string& source, const std::vector<std::shared_ptr<IRenderableShape>>& shapes);

        const std::string& getSource() const override;

        const std::vector<std::shared_ptr<IRenderableShape>>& getShapes() const override;

    private:
        std::string _source;
        std::vector<std::shared_ptr<IRenderableShape>> _shapes;
    };
}