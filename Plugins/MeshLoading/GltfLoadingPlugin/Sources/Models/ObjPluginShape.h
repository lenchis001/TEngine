#include "IPluginShape.h"

#include "vector"

using namespace TEngine::Components::Graphics::MeshLoading::Plugin;

namespace ObjLoadingPlugin::Models
{
    class ObjPluginShape : public IPluginShape
    {
    public:
        ObjPluginShape(
            const std::string &name,
            const std::vector<float> &vertices,
            const std::vector<float> &normals,
            const std::vector<float> &uvs,
            const std::vector<float> &diffuseColor,
            const std::string &texturePath);

        const std::string &getName() override;

        const std::vector<float> &getVertices() const override;

        const std::vector<float> &getNormals() const override;

        const std::vector<float> &getUVs() const override;

        const std::vector<float> &getDiffuseColor() const override;

        const std::string &getTexturePath() const override;
    private:
        std::string _name;
        std::vector<float> _vertices;
        std::vector<float> _normals;
        std::vector<float> _uvs;
        std::vector<float> _diffuseColor;
        std::string _texturePath;
    };
}