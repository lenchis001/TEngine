#ifndef OBJ_LOADING_PLUGIN_H
#define OBJ_LOADING_PLUGIN_H

#include <vector>
#include <string>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include "IMeshLoadingPlugin.h"

using namespace tinygltf;

using namespace TEngine::Components::Graphics::MeshLoading::Plugin;

namespace ObjLoadingPlugin
{
    class GltfLoadingPluginImplementation : public IMeshLoadingPlugin
    {
    public:
        GltfLoadingPluginImplementation();
        virtual ~GltfLoadingPluginImplementation() override;

        virtual std::vector<std::string> getSupportedExtensions() const override;

        virtual std::shared_ptr<IPluginMesh> load(const std::vector<uint8_t>& data, const std::string& basePath) override;

    private:
        std::vector<uint32_t> extractIndices(const tinygltf::Model& model, const tinygltf::Accessor& indexAccessor) const;
        std::vector<float> extractVertices(const tinygltf::Model& model, const tinygltf::Accessor& positionAccessor, const std::vector<uint32_t>& indices) const;
        std::vector<float> extractNormals(const tinygltf::Model& model, const tinygltf::Accessor& normalAccessor, const std::vector<uint32_t>& indices) const;
        std::vector<float> extractUVs(const tinygltf::Model& model, const tinygltf::Accessor& uvAccessor, const std::vector<uint32_t>& indices) const;
        std::string extractTexturePath(const tinygltf::Model& model, const tinygltf::Material& material, const std::string& basePath) const;
    };
}

extern "C"
{
    std::shared_ptr<IMeshLoadingPlugin> load();
}

#endif // OBJ_LOADING_PLUGIN_H