#include "GltfLoadingPluginImplementation.h"

#include <iostream>
#include <sstream>
#include <string>

#define TINYGLTF_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "tiny_gltf.h"

#include "boost/filesystem.hpp"

#include "Models/ObjPluginShape.h"
#include "Models/ObjPluginMesh.h"

using namespace tinygltf;

using namespace ObjLoadingPlugin;
using namespace ObjLoadingPlugin::Models;

GltfLoadingPluginImplementation::GltfLoadingPluginImplementation()
{
}

GltfLoadingPluginImplementation::~GltfLoadingPluginImplementation()
{
}

std::vector<std::string> GltfLoadingPluginImplementation::getSupportedExtensions() const
{
    return std::vector<std::string>{"glb"};
}

std::shared_ptr<IPluginMesh> GltfLoadingPluginImplementation::load(const std::vector<uint8_t> &data, const std::string &basePath)
{
    std::istringstream stream(std::string(reinterpret_cast<const char *>(data.data()), data.size()));

    Model model;
    TinyGLTF loader;
    std::string err;
    std::string warn;

    if (!loader.LoadBinaryFromMemory(&model, &err, &warn, data.data(), data.size(), basePath))
    {
        return nullptr;
    }

    std::vector<std::shared_ptr<IPluginShape>> shapes;

    for (const auto &mesh : model.meshes)
    {
        for (const auto &primitive : mesh.primitives)
        {
            if (primitive.indices < 0)
                continue;

            std::vector<uint32_t> indices;
            const auto &indexAccessor = model.accessors[primitive.indices];
            const auto &indexBufferView = model.bufferViews[indexAccessor.bufferView];
            const auto &indexBuffer = model.buffers[indexBufferView.buffer];
            const uint16_t *indexData = reinterpret_cast<const uint16_t *>(&indexBuffer.data[indexBufferView.byteOffset]);

            for (size_t i = 0; i < indexAccessor.count; ++i)
            {
                indices.push_back(indexData[i]);
            }

            std::vector<float> vertices;
            std::vector<float> normals;
            std::vector<float> uvs;

            auto floatSize = sizeof(float);
            const auto &positionAccessor = model.accessors[primitive.attributes.at("POSITION")];
            const auto &positionBufferView = model.bufferViews[positionAccessor.bufferView];
            const auto &positionBuffer = model.buffers[positionBufferView.buffer];
            const float *positionData = reinterpret_cast<const float *>(&positionBuffer.data[positionBufferView.byteOffset]);

            for (size_t i = 0; i < indexAccessor.count; ++i)
            {
                uint32_t vertexIndex = indexData[i]; // Индекс вершины
                vertices.push_back(positionData[vertexIndex * 3 + 0]); // X
                vertices.push_back(positionData[vertexIndex * 3 + 1]); // Y
                vertices.push_back(positionData[vertexIndex * 3 + 2]); // Z
            }

            if (primitive.attributes.find("NORMAL") != primitive.attributes.end())
            {
                const auto &normalAccessor = model.accessors[primitive.attributes.at("NORMAL")];
                const auto &normalBufferView = model.bufferViews[normalAccessor.bufferView];
                const auto &normalBuffer = model.buffers[normalBufferView.buffer];
                const float *normalData = reinterpret_cast<const float *>(&normalBuffer.data[normalBufferView.byteOffset]);

                for (size_t i = 0; i < indexAccessor.count; ++i)
                {
                    uint32_t vertexIndex = indexData[i]; // Индекс вершины
                    normals.push_back(normalData[vertexIndex * 3 + 0]); // X
                    normals.push_back(normalData[vertexIndex * 3 + 1]); // Y
                    normals.push_back(normalData[vertexIndex * 3 + 2]); // Z
                }
            }

            if (primitive.attributes.find("TEXCOORD_0") != primitive.attributes.end())
            {
                const auto &uvAccessor = model.accessors[primitive.attributes.at("TEXCOORD_0")];
                const auto &uvBufferView = model.bufferViews[uvAccessor.bufferView];
                const auto &uvBuffer = model.buffers[uvBufferView.buffer];
                const float *uvData = reinterpret_cast<const float *>(&uvBuffer.data[uvBufferView.byteOffset]);

                for (size_t i = 0; i < indexAccessor.count; ++i)
                {
                    uint32_t vertexIndex = indexData[i]; // Индекс вершины
                    uvs.push_back(uvData[vertexIndex * 2 + 0]); // U
                    uvs.push_back(uvData[vertexIndex * 2 + 1]); // V
                }
            }

            std::vector<float> diffuseColor = {0.f, 0.f, 0.f};
            std::string texturePath;

            if (primitive.material >= 0)
            {
                const auto &material = model.materials[primitive.material];
                if (material.pbrMetallicRoughness.baseColorFactor.size() == 4)
                {
                    // diffuseColor[0] = static_cast<float>(material.pbrMetallicRoughness.baseColorFactor[0]);
                    // diffuseColor[1] = static_cast<float>(material.pbrMetallicRoughness.baseColorFactor[1]);
                    // diffuseColor[2] = static_cast<float>(material.pbrMetallicRoughness.baseColorFactor[2]);
                }

                if (material.pbrMetallicRoughness.baseColorTexture.index >= 0)
                {
                    const auto &texture = model.textures[material.pbrMetallicRoughness.baseColorTexture.index];
                    if (texture.source >= 0)
                    {
                        const auto &image = model.images[texture.source];
                        if (!image.uri.empty())
                        {
                            texturePath = boost::filesystem::absolute(image.uri, basePath).string();
                        }
                        else if (!image.name.empty() && !image.mimeType.empty())
                        {
                            std::string extension;
                            if (image.mimeType == "image/png")
                            {
                                extension = ".png";
                            }
                            else if (image.mimeType == "image/jpeg")
                            {
                                extension = ".jpg";
                            }
                            // Add more mime types if needed
                            texturePath = boost::filesystem::absolute(image.name + extension, basePath).string();
                        }
                    }
                }
            }

            shapes.push_back(std::make_shared<ObjPluginShape>(
                mesh.name,
                vertices,
                normals,
                uvs,
                diffuseColor,
                texturePath));
        }
    }

    return std::make_shared<ObjPluginMesh>(shapes);
}

std::shared_ptr<IMeshLoadingPlugin> load()
{
    return std::make_shared<GltfLoadingPluginImplementation>();
}