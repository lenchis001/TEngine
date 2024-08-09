#ifndef TENGINE_ERRORCODES_H
#define TENGINE_ERRORCODES_H

namespace TEngine::Components::Graphics::MeshLoading::Models
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

#endif //TENGINE_ERRORCODES_H