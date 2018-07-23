#ifndef TENGINE_MESHLOADING_ERRORCODES_H
#define TENGINE_MESHLOADING_ERRORCODES_H

namespace TEngine::Components::Graphics::Models::MeshLoading
{
    enum class MeshLoadingErrorCodes
    {
        FILE_NOT_FOUND,
        FILE_NOT_SUPPORTED,
        FILE_CORRUPTED,
        FILE_EMPTY,
        FILE_READ_ERROR,
        FILE_PARSE_ERROR,
        FILE_FORMAT_ERROR,
        FILE_DATA_ERROR,
        FILE_UNKNOWN_ERROR
    };
}

#endif //TENGINE_MESHLOADING_ERRORCODES_H