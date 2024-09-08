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

    // positions
    for (auto &position : result.attributes.positions)
    {
        std::cout << "position: " << position << std::endl;
    }

    for (const auto &shape : result.shapes)
    {
        std::vector<float> vertices;

        for (auto &indice : shape.mesh.indices)
        {
            auto positionIndex = indice.position_index * 3;
            auto x = result.attributes.positions[positionIndex];
            auto y = result.attributes.positions[positionIndex + 1];
            auto z = result.attributes.positions[positionIndex + 2];

            vertices.push_back(x);
            vertices.push_back(y);
            vertices.push_back(z);
        }

        shapes.push_back(std::make_shared<ObjPluginShape>(
            shape.name,
            vertices,
            std::vector<std::string>(),
            std::vector<float>(),
            std::vector<float>()));
    }

    return std::make_shared<ObjPluginMesh>(shapes);
}

std::shared_ptr<IMeshLoadingPlugin> load()
{
    return std::make_shared<ObjLoadingPluginImplementation>();
}