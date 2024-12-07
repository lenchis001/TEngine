#ifndef TENGINE_INDEXING_IINDEXINGSERVICE_H
#define TENGINE_INDEXING_IINDEXINGSERVICE_H

#include <vector>

namespace TEngine::Components::Graphics::Indexing
{
    class IIndexingService
    {
    public:
        virtual std::vector<unsigned> index(
            std::vector<float> &vertices,
            std::vector<float> &uvs,
            std::vector<float> &normals) = 0;
    };
}

#endif // TENGINE_INDEXING_IINDEXINGSERVICE_H