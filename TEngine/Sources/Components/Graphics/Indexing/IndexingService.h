#include "IIndexingService.h"

namespace TEngine::Components::Graphics::Indexing
{
    class IndexingService : public IIndexingService
    {
    public:
        std::vector<unsigned> index(
            std::vector<float> &vertices,
            std::vector<float> &uvs,
            std::vector<float> &normals) override;

    private:
        size_t _findIndex(
            const std::vector<float> &indexedVertices,
            const std::vector<float> &indexedUvs,
            const std::vector<float> &indexedNormals,
            float *vertex,
            float *uv,
            float *normal);
    };
}