#include "IndexingService.h"

#include <cstring>
#include <limits>

using namespace TEngine::Components::Graphics::Indexing;

std::vector<unsigned> IndexingService::index(
    std::vector<float> &vertices,
    std::vector<float> &uvs,
    std::vector<float> &normals)
{
    std::vector<float> indexedVertices;
    std::vector<float> indexedUvs;
    std::vector<float> indexedNormals;

    auto areUvsProvided = !uvs.empty();
    auto areNormalsProvided = !normals.empty();

    std::vector<unsigned> indexes;

    for (size_t i = 0; i < vertices.size() / 3; i++)
    {
        auto vertexPosition = i * 3;
        auto uvPosition = i * 2;
        auto normalPosition = i * 3;

        auto vertex = &vertices[vertexPosition];
        auto uv = areUvsProvided ? &uvs[uvPosition] : nullptr;
        auto normal = areNormalsProvided ? &normals[normalPosition] : nullptr;

        auto index = _findIndex(indexedVertices, indexedUvs, indexedNormals, vertex, uv, normal);

        if (index == std::numeric_limits<size_t>::max())
        {
            // Add new vertex to indexed vertices
            indexedVertices.push_back(vertex[0]);
            indexedVertices.push_back(vertex[1]);
            indexedVertices.push_back(vertex[2]);

            // Add new uv to indexed uvs
            if (areUvsProvided)
            {
                indexedUvs.push_back(uv[0]);
                indexedUvs.push_back(uv[1]);
            }

            // Add new normal to indexed normals
            if (areNormalsProvided)
            {
                indexedNormals.push_back(normal[0]);
                indexedNormals.push_back(normal[1]);
                indexedNormals.push_back(normal[2]);
            }

            indexes.push_back(indexedVertices.size() / 3 - 1);
        }
        else
        {
            indexes.push_back(index);
        }
    }

    vertices.swap(indexedVertices);
    uvs.swap(indexedUvs);
    normals.swap(indexedNormals);

    return indexes;
}

size_t IndexingService::_findIndex(
    const std::vector<float> &indexedVertices,
    const std::vector<float> &indexedUvs,
    const std::vector<float> &indexedNormals,
    float *vertex,
    float *uv,
    float *normal)
{
    for (size_t i = 0; i < indexedVertices.size() / 3; i++)
    {
        auto indexedVertexPosition = i * 3;
        auto indexedUvPosition = i * 2;
        auto indexedNormalPosition = i * 3;

        if (memcmp(vertex, &indexedVertices[indexedVertexPosition], sizeof(float) * 3) == 0 &&
            (uv == nullptr || memcmp(uv, &indexedUvs[indexedUvPosition], sizeof(float) * 2) == 0) &&
            (normal == nullptr || memcmp(normal, &indexedNormals[indexedNormalPosition], sizeof(float) * 3) == 0))
        {
            return i;
        }
    }

    return std::numeric_limits<size_t>::max();
}