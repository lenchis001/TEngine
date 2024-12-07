#include "GL/glew.h"

#include <cassert>
#include <iostream>

#include "MeshService.h"

#include "Components/Graphics/Rendering/Models/Meshes/RenderableMesh.h"
#include "Components/Graphics/Rendering/Models/Meshes/RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Scene::Meshes;

#define COLORED_VERTEX_SHADER_SOURCE "BuildinResources/Shaders/Mesh/ColoredShapeVertexShader.glsl"
#define COLORED_FRAGMENT_SHADER_SOURCE "BuildinResources/Shaders/Mesh/ColoredShapeFragmentShader.glsl"
#define TEXTURED_VERTEX_SHADER_SOURCE "BuildinResources/Shaders/Mesh/TexturedShapeVertexShader.glsl"
#define TEXTURED_FRAGMENT_SHADER_SOURCE "BuildinResources/Shaders/Mesh/TexturedShapeFragmentShader.glsl"

#define toVertexName(name) name + "Vertices"
#define toNormalName(name) name + "Normals"
#define toUvName(name) name + "UVs"
#define toIndexName(name) name + "Indexes"

MeshService::MeshService(
    std::shared_ptr<IMeshLoadingService> meshLoadingService,
    std::shared_ptr<IBuffersService> buffersService,
    std::shared_ptr<IShadersService> shadersService,
    std::shared_ptr<ITexturesService> texturesService,
    std::shared_ptr<IIndexingService> indexingService)
    : _meshLoadingService(meshLoadingService),
      _buffersService(buffersService),
      _shadersService(shadersService),
      _texturesService(texturesService),
      _indexingService(indexingService)
{
}

MeshService::~MeshService()
{
    assert(_renderableMeshes.empty() && "All renderable meshes should be released before MeshService destruction");
}

std::shared_ptr<IRenderableMesh> MeshService::take(const std::string &path)
{
    auto renderableMeshIterator = _renderableMeshes.find(path);
    if (renderableMeshIterator != _renderableMeshes.end())
    {
        renderableMeshIterator->second.first++;

        return renderableMeshIterator->second.second;
    }

    auto mesh = _meshLoadingService->load(path);

    std::vector<std::shared_ptr<IRenderableShape>> renderableShapes;

    for (auto &shape : mesh->getShapes())
    {
        renderableShapes.push_back(_toRenderableShape(shape, path));
    }

    auto renderableMesh = std::make_shared<RenderableMesh>(path, renderableShapes);
    _renderableMeshes[path] = {1, renderableMesh};

    return renderableMesh;
}

void MeshService::release(std::shared_ptr<IRenderableMesh> renderableMesh)
{
    auto renderableMeshIterator = _renderableMeshes.find(renderableMesh->getSource());
    assert(renderableMeshIterator != _renderableMeshes.end() && "Renderable mesh should be taken before releasing");

    renderableMeshIterator->second.first--;

    if (renderableMeshIterator->second.first == 0)
    {
        _renderableMeshes.erase(renderableMeshIterator);
        for (auto &shape : renderableMesh->getShapes())
        {
            _buffersService->releaseVbo(toVertexName(shape->getName()));
            _buffersService->releaseVbo(toNormalName(shape->getName()));
            if (shape->isTextured())
                _buffersService->releaseVbo(toUvName(shape->getName()));
            _buffersService->releaseVao(shape->getName());
            _buffersService->releaseVbo(toIndexName(shape->getName()));
            _shadersService->release(shape->getProgram());

            if (shape->getTextureId() != 0)
                _texturesService->release(shape->getTextureId());
        }
    }
}

std::shared_ptr<IRenderableShape> MeshService::_toRenderableShape(std::shared_ptr<IShape> shape, const std::string &path)
{
    std::vector<float> indexedVertexes = shape->getVertices();
    std::vector<float> indexedUvs = shape->getUVs();
    std::vector<float> indexedNormals = shape->getNormals();

    auto indexes = _indexingService->index(indexedVertexes, indexedUvs, indexedNormals);

    auto name = path + shape->getName();

    // Prepare vertices VBO
    auto verticesBufferName = toVertexName(name);

    auto verticesBuffer = _buffersService->takeVbo(verticesBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);

    glBufferData(GL_ARRAY_BUFFER, indexedVertexes.size() * sizeof(unsigned), indexedVertexes.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Prepare normals VBO
    auto normalsBufferName = toNormalName(name);

    auto normalsBuffer = _buffersService->takeVbo(normalsBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);

    glBufferData(GL_ARRAY_BUFFER, indexedNormals.size() * sizeof(float), indexedNormals.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Prepare UVs VBO
    auto texPath = shape->getTexturePath();
    auto isTextured = shape->isTextured();

    GLuint uvsBuffer = 0;
    if (isTextured)
    {
        auto uvsBufferName = toUvName(name);

        uvsBuffer = _buffersService->takeVbo(uvsBufferName);
        glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);

        glBufferData(GL_ARRAY_BUFFER, indexedUvs.size() * sizeof(float), indexedUvs.data(), GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    // Prepare VAO
    auto vao = _buffersService->takeVao(name);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    if (isTextured)
    {
        glEnableVertexAttribArray(2);
        glBindBuffer(GL_ARRAY_BUFFER, uvsBuffer);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    }

    glBindVertexArray(0);

    // Prepare index buffer
    auto indexBufferName = toIndexName(name);

    auto indexBuffer = _buffersService->takeVbo(indexBufferName);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexes.size() * sizeof(unsigned int), indexes.data(), GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // Prepare program
    auto vertedShader = isTextured ? TEXTURED_VERTEX_SHADER_SOURCE : COLORED_VERTEX_SHADER_SOURCE;
    auto fragmentShader = isTextured ? TEXTURED_FRAGMENT_SHADER_SOURCE : COLORED_FRAGMENT_SHADER_SOURCE;
    auto program = _shadersService->take(vertedShader, fragmentShader);

    auto mvpMatrixShaderId = glGetUniformLocation(program, "MVP");
    auto modelMatrixShaderId = glGetUniformLocation(program, "modelMatrix");
    auto viewMatrixShaderId = glGetUniformLocation(program, "viewMatrix");
    auto lightPosShaderId = glGetUniformLocation(program, "lightPosition");
    auto lightColorShaderId = glGetUniformLocation(program, "lightColor");
    auto lightPowerShaderId = glGetUniformLocation(program, "lightPower");
    auto shapeColorShaderId = glGetUniformLocation(program, "shapeColor");

    // Prepare texture
    GLuint textureId;

    if (isTextured)
    {
        textureId = _texturesService->take(shape->getTexturePath());
    }
    else
    {
        textureId = 0;
    }

    return std::make_shared<RenderableShape>(
        name,
        vao,
        indexBuffer,
        shape->getVertices(),
        program,
        mvpMatrixShaderId,
        modelMatrixShaderId,
        viewMatrixShaderId,
        lightPosShaderId,
        lightColorShaderId,
        lightPowerShaderId,
        shapeColorShaderId,
        shape->getDiffuseColor(),
        textureId);
}