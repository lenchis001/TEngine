#ifndef TENGINE_PLUGIN_ISHAPE_H
#define TENGINE_PLUGIN_ISHAPE_H

#include "string"
#include "vector"

namespace TEngine::Components::Graphics::MeshLoading::Plugin
{
    class IPluginShape
    {
    public:
        virtual ~IPluginShape() = default;

        virtual const std::string &getName() const = 0;

        virtual const std::vector<float> &getVertices() const = 0;

        virtual const std::vector<std::string> &getTextures() const = 0;

        virtual const std::vector<float> &getNormals() const = 0;

        virtual const std::vector<float> &getUVs() const = 0;

        
    };
}

#endif // TENGINE_PLUGIN_ISHAPE_H