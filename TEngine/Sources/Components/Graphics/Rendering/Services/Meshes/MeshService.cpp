#include "GL/glew.h"

#include "MeshService.h"

#include "Components/Graphics/Rendering/Models/Meshes/RenderableMesh.h"
#include "Components/Graphics/Rendering/Models/Meshes/RenderableShape.h"

using namespace TEngine::Components::Graphics::Rendering::Services::Meshes;

#define VERTEX_SHADER_SOURCE "BuildinResources/Shaders/Mesh/ColoredShapeVertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "BuildinResources/Shaders/Mesh/ColoredShapeFragmentShader.glsl"

#define toVertexName(name) name + "Vertices"
#define toNormalName(name) name + "Normals"

MeshService::MeshService(
    std::shared_ptr<IMeshLoadingService> meshLoadingService,
    std::shared_ptr<IBuffersService> buffersService,
    std::shared_ptr<IShadersService> shadersService)
    : _meshLoadingService(meshLoadingService),
      _buffersService(buffersService),
      _shadersService(shadersService)
{
}

std::shared_ptr<IRenderableMesh> MeshService::take(const std::string &path)
{
    auto mesh = _meshLoadingService->load(path);

    std::vector<std::shared_ptr<IRenderableShape>> renderableShapes;

    for (auto &shape : mesh->getShapes())
    {
        renderableShapes.push_back(_toRenderableShape(shape, path));
    }

    return std::make_shared<RenderableMesh>(renderableShapes);
}

void MeshService::release(std::shared_ptr<IRenderableMesh> renderableMesh)
{
    for (auto &shape : renderableMesh->getShapes())
    {
        _buffersService->releaseVbo(toVertexName(shape->getName()));
        _buffersService->releaseVbo(toNormalName(shape->getName()));
        _buffersService->releaseVao(shape->getName());
        _shadersService->release(shape->getProgram());
    }
}

std::shared_ptr<IRenderableShape> MeshService::_toRenderableShape(std::shared_ptr<IShape> shape, const std::string &path)
{
    auto name = path + shape->getName();

    // Prepare vertices VBO
    auto verticesBufferName = toVertexName(name);

    auto verticesBuffer = _buffersService->takeVbo(verticesBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);

    const auto &vertices = shape->getVertices();
    auto verticesCount = vertices.size();
    glBufferData(GL_ARRAY_BUFFER, verticesCount * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Prepare normals VBO
    auto normalsBufferName = toNormalName(name);

    auto normalsBuffer = _buffersService->takeVbo(normalsBufferName);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);

    const auto &normals = shape->getNormals();
    auto normalsCount = normals.size();
    glBufferData(GL_ARRAY_BUFFER, normalsCount * sizeof(float), normals.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Prepare VAO
    auto vao = _buffersService->takeVao(name);

    glBindVertexArray(vao);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, normalsBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindVertexArray(0);

    // Prepare program
    auto program = _shadersService->take(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

    auto mvpMatrixShaderId = glGetUniformLocation(program, "MVP");
    auto modelMatrixShaderId = glGetUniformLocation(program, "modelMatrix");
    auto viewMatrixShaderId = glGetUniformLocation(program, "viewMatrix");
    auto lightPosShaderId = glGetUniformLocation(program, "lightPosition");
    auto lightColorShaderId = glGetUniformLocation(program, "lightColor");
    auto lightPowerShaderId = glGetUniformLocation(program, "lightPower");

    return std::make_shared<RenderableShape>(
        name,
        vao,
        verticesCount,
        program,
        mvpMatrixShaderId,
        modelMatrixShaderId,
        viewMatrixShaderId,
        lightPosShaderId,
        lightColorShaderId,
        lightPowerShaderId);
}