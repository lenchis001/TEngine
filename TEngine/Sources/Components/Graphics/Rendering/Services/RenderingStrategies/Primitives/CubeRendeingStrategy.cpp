#include "GL/glew.h"

#include "CubeRenderingStrategy.h"

using namespace TEngine::Components::Graphics::Rendering::Services::RenderingStrategies::Primitives;

#define VERTEX_SHADER_SOURCE "BuildinResources/Shaders/SimpleVertexShader.glsl"
#define FRAGMENT_SHADER_SOURCE "BuildinResources/Shaders/SimpleFragmentShader.glsl"

#define VERTEX_VBO_INDEX 0
#define COLOR_VBO_INDEX 1

CubeRenderingStrategy::CubeRenderingStrategy(std::shared_ptr<IRenderableObject> cube, std::shared_ptr<IShadersService> shadersService)
    : BufferCacheAware(typeid(CubeRenderingStrategy)), _cube(cube), _shadersService(shadersService)
{
    _prepareVertexVbo();
    _prepareColorVbo();
    _prepareVao();
    _prepareShader();
}

void CubeRenderingStrategy::render(const Matrix4x4f &vpMatrix)
{
    glBindVertexArray(getCachedVao());

    glUseProgram(_shaderProgram);

    const auto &modelMatrix = _cube->getModelMatrix();
    auto mvp = vpMatrix * modelMatrix;

    glUniformMatrix4fv(_matrixId, 1, GL_FALSE, mvp.getInternalData());

    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6 /*sides*/ * 2 /*triangles in every one*/ * 3 /*verteces in every one*/);

    glUseProgram(0);

    glBindVertexArray(0);
}

void CubeRenderingStrategy::_prepareVertexVbo()
{
    GLuint vbo;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, -1.0f,
        1.0f, -1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, -1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, -1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    setCachedVbo(vbo, VERTEX_VBO_INDEX);
}

void CubeRenderingStrategy::_prepareColorVbo()
{
    GLuint vbo;

    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);

    GLfloat colors[] = {
        0.583f, 0.771f, 0.014f,
        0.609f, 0.115f, 0.436f,
        0.327f, 0.483f, 0.844f,
        0.822f, 0.569f, 0.201f,
        0.435f, 0.602f, 0.223f,
        0.310f, 0.747f, 0.185f,
        0.597f, 0.770f, 0.761f,
        0.559f, 0.436f, 0.730f,
        0.359f, 0.583f, 0.152f,
        0.483f, 0.596f, 0.789f,
        0.559f, 0.861f, 0.639f,
        0.195f, 0.548f, 0.859f,
        0.014f, 0.184f, 0.576f,
        0.771f, 0.328f, 0.970f,
        0.406f, 0.615f, 0.116f,
        0.676f, 0.977f, 0.133f,
        0.971f, 0.572f, 0.833f,
        0.140f, 0.616f, 0.489f,
        0.997f, 0.513f, 0.064f,
        0.945f, 0.719f, 0.592f,
        0.543f, 0.021f, 0.978f,
        0.279f, 0.317f, 0.505f,
        0.167f, 0.620f, 0.077f,
        0.347f, 0.857f, 0.137f,
        0.055f, 0.953f, 0.042f,
        0.714f, 0.505f, 0.345f,
        0.783f, 0.290f, 0.734f,
        0.722f, 0.645f, 0.174f,
        0.302f, 0.455f, 0.848f,
        0.225f, 0.587f, 0.040f,
        0.517f, 0.713f, 0.338f,
        0.053f, 0.959f, 0.120f,
        0.393f, 0.621f, 0.362f,
        0.673f, 0.211f, 0.457f,
        0.820f, 0.883f, 0.371f,
        0.982f, 0.099f, 0.879f};

    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    setCachedVbo(vbo, COLOR_VBO_INDEX);
}

void CubeRenderingStrategy::_prepareVao()
{
    GLuint vao;

    glGenVertexArrays(1, &vao);

    glBindVertexArray(vao);

    // Bind and activate vertex VBO
    glBindBuffer(GL_ARRAY_BUFFER, getCachedVbo(VERTEX_VBO_INDEX));
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    // Bind and activate color VBO
    glBindBuffer(GL_ARRAY_BUFFER, getCachedVbo(COLOR_VBO_INDEX));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    setCachedVao(vao);
}

void CubeRenderingStrategy::_prepareShader()
{
    _shaderProgram = _shadersService->loadShader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);

    _matrixId = glGetUniformLocation(_shaderProgram, "MVP");
}