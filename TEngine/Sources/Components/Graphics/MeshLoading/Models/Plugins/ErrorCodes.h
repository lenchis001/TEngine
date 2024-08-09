#ifndef TENGINE_MESH_LOADING_PLUGIN_ERRORCODES_H
#define TENGINE_MESH_LOADING_PLUGIN_ERRORCODES_H

namespace TEngine::Components::Graphics::MeshLoading::Models::Plugins
{
    enum class ErrorCodes
    {
        NOT_FOUND,
        NOT_SUPPORTED,
        CORRUPTED,
        EMPTY,
        READ_ERROR,
        PARSE_ERROR,
        UNKNOWN_ERROR
    };
}

#endif //TENGINE_MESH_LOADING_PLUGIN_ERRORCODES_H