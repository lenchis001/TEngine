#include "ObjLoadingPluginImplementation.h"

#include "memory"
#include "iostream"

#include "rapidobj/rapidobj.hpp"

#include "Models/ObjPluginShape.h"
#include "Models/ObjPluginMesh.h"

using namespace rapidobj;

using namespace ObjLoadingPlugin;
using namespace ObjLoadingPlugin::Models;

ObjLoadingPluginImplementation::ObjLoadingPluginImplementation()
{
}

ObjLoadingPluginImplementation::~ObjLoadingPluginImplementation()
{
}

std::vector<std::string> ObjLoadingPluginImplementation::getSupportedExtensions() const
{
    return std::vector<std::string>{"obj"};
}

std::shared_ptr<IPluginMesh> ObjLoadingPluginImplementation::load(const std::string &path)
{
    auto result = ParseFile(path);

    if (result.error)
    {
        return nullptr;
    }

    Triangulate(result);

    std::vector<std::shared_ptr<IPluginShape>> shapes;

    for (const auto &shape : result.shapes)
    {
        std::vector<float> vertices;
        std::vector<float> normals;
        std::vector<float> uvs;

        std::vector<float> diffuseColor(3);
        std::string texturePath;
        if (!shape.mesh.material_ids.empty())
        {
            auto material = result.materials[shape.mesh.material_ids[0]];
            diffuseColor[0] = material.diffuse[0];
            diffuseColor[1] = material.diffuse[1];
            diffuseColor[2] = material.diffuse[2];

            texturePath = material.diffuse_texname;
        }
        else
        {
            diffuseColor = {.3f, .3f, .3f};
        }

        for (auto &indice : shape.mesh.indices)
        {
            auto positionIndex = indice.position_index * 3;
            auto x = result.attributes.positions[positionIndex];
            auto y = result.attributes.positions[positionIndex + 1];
            auto z = result.attributes.positions[positionIndex + 2];

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);

            auto normalIndex = indice.normal_index * 3;
            auto nx = result.attributes.normals[normalIndex];
            auto ny = result.attributes.normals[normalIndex + 1];
            auto nz = result.attributes.normals[normalIndex + 2];

            normals.push_back(nx);
            normals.push_back(ny);
            normals.push_back(nz);

            if (indice.texcoord_index != -1)
            {
                auto uvIndex = indice.texcoord_index * 2;
                auto u = result.attributes.texcoords[uvIndex];
                auto v = result.attributes.texcoords[uvIndex + 1];
                uvs.push_back(u);
                uvs.push_back(v);
            }
        }

        shapes.push_back(std::make_shared<ObjPluginShape>(
            shape.name,
            vertices,
            normals,
            uvs,
            diffuseColor,
            texturePath));
    }

    return std::make_shared<ObjPluginMesh>(shapes);
}

std::shared_ptr<IMeshLoadingPlugin> load()
{
    return std::make_shared<ObjLoadingPluginImplementation>();
}