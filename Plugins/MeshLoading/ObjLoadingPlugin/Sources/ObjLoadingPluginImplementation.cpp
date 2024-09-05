#include "ObjLoadingPluginImplementation.h"

#include "memory"

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

    std::vector<std::shared_ptr<IPluginShape>> shapes;

    for (const auto &shape : result.shapes)
    {
        std::vector<float> vertices;

        for (auto &indice : shape.mesh.indices)
        {
            vertices.push_back(result.attributes.positions[indice.position_index]);
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